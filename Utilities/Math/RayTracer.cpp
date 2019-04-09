#include "RayTracer.h"

RayTracer::RayTracer(Camera c) : depth_buffer(c.getViewWidth(), c.getViewHeight())
{
    ambient_coefficient = 0.2;
    diffuse_coefficient = 0.2;
    specular_coefficient = 0.2;

    camera = c;
    //now we need to add the rays to our ray container
    //we need to do this for each pixel that the camera can see.
    //therefore we need the view width and height of the camera
    int view_width = camera.getViewWidth();
    int view_height = camera.getViewHeight();

    image = cimg_library::CImg<unsigned char>(view_width, view_height, 1, 3);
    image.fill(0);
}

void RayTracer::trace(std::vector<SceneObject*> s)
{
    scene_objects = s;

    for(int i = 0; i < s.size(); i++)
    {
        if(isSphere(s[i]))
            trace(*(dynamic_cast<Sphere*>(s[i])));
        if(isPlane(s[i]))
        {
            plane = *(dynamic_cast<Plane*>(s[i]));
            trace(*(dynamic_cast<Plane*>(s[i])));
        }

    }
}

void RayTracer::trace(Sphere s)
{
    //to trace the sphere, we need to check for each of the rays in our ray container, if they intersect with this sphere
    //to know this, we need to solve the following equation
    //O^2 + D^2t^2 + 2ODt - R^2 = 0
    //where O is the origin of the camera (its position)
    //D is the direction vector, the vec3 in our current ray
    //t is a variable we are solving for
    //and R is the radius of the sphere

    //the origin and the radius do not change
    Vec3 O = camera.getPosition();
    float R = s.getRadius();
    Vec3 C = s.getPosition(); //center of the sphere
    Vec3 OtoC = O-C;
    float x1, x2; //these will store the solution to the quadratic equation, if there is one
    float a = 0;
    float b = 0;
    float c = 0; //these are the parameters for the quadratic equation we will be solving

    std::cout << "Processing Sphere..." << std::endl;

    int view_width = camera.getViewWidth();
    int view_height = camera.getViewHeight();

    Ray ray;
    Vec3 normal;
    Vec3 intersection_point;

    depth_buffer.reset();

    for(int x = 0; x < view_width; x++)
    {
        for(int y = 0; y < view_height; y++)
        {
            //iterate over each "pixel" that the camera can see and set the ray for that pixel
            ray.setRay(Vec3(view_width/2-x, y - view_height/2, camera.getFocalLength()));
            ray.setPixel(Pixel(x, y));
            ray.getRay().normalize();

            a = ray.getRay().square();
            b = 2*ray.getRay().dot(OtoC);
            c = OtoC.square() - R*R;

            if(quadratic_solve(a, b, c, x1, x2))
            {
                //if we have a solution, we need to compute the lighting for that point
                //this needs to be done for every light in our vector of lights

                //the three color channels
                float red = 0;
                float green = 0;
                float blue = 0;

                //for each light we need to get the direction from the light to the intersection points
                //in order to do this, we first need to find those intersection points

                Vec3 ray_direction = ray.getRay();
                intersection_point = getSphereIntersection(camera.getPosition(), ray_direction, x1, x2);

                //now that we have the intersection points, we need to compute the normals at this point
                //for the sphere, this is done by taking the difference between the point and the center of the
                //sphere and then normalizing it
                normal = intersection_point - s.getPosition();
                normal.normalize();

                //we need to check if the z value of this intersection is closer than the closest depth recorded
                //in the depth buffer

                if((camera.getPosition() - intersection_point).length() >
                   depth_buffer.getCurrentDepth())
                {
                    //if the depth is greater, we don't want to draw that point and so we should break
                    continue;
                }

                else
                {
                    //if the  depth of the intersection is closer than what is in the depth buffer, then we color
                    //in the pixel
                    //update the depth buffer
                    depth_buffer.setCurrentDepth((camera.getPosition() - intersection_point).length());
                }

                for(int l = 0; l < lights.size(); l++)
                {

                    //we only want to keep the closest intersection point so we don't draw for no reason

                    //now we need to calculate the diffuse strength for each of these points
                    //the diffuse strength is the dot product of the light direction and the surface normal
                    //if the light direction is parallel to the normal this is highest intensity = 1
                    //if it is perpendicular then the intensity is 0
                    Vec3 light_direction = intersection_point - lights[l].getPosition();
                    light_direction.normalize();
                    float diffuse_strength = light_direction.dot(normal);
                    clamp(diffuse_strength, 0, 1);

                    //the next step is to calculate the specular strength
                    //in order to do this, we need to take the dot of the reflected light vector about the normal
                    //and the view vector, which is the ray direction and raise it to the shininess
                    Vec3 reflection = light_direction.reflect(normal);
                    reflection.normalize();
                    ray_direction.normalize();
                    float spec_strength = ray_direction.dot(reflection);
                    clamp(spec_strength, 0, 1);
                    spec_strength = pow(spec_strength, s.getShininess());

                    //now we calculate the color of the pixel
                    red += ambient_coefficient*s.getAmbientColor().x
                            + diffuse_coefficient*diffuse_strength*s.getDiffuseColor().x
                            + specular_coefficient*spec_strength*s.getSpecularColor().x;
                    green += ambient_coefficient*s.getAmbientColor().y
                           + diffuse_coefficient*diffuse_strength*s.getDiffuseColor().y
                           + specular_coefficient*spec_strength*s.getSpecularColor().y;
                    blue += ambient_coefficient*s.getAmbientColor().z
                           + diffuse_coefficient*diffuse_strength*s.getDiffuseColor().z
                           + specular_coefficient*spec_strength*s.getSpecularColor().z;

                    //now that we have computed the colors from the lighting we need to check if this pixel should be
                    //in shadow. This will be the case if there is another object between it and the light.
                    //therefore we need to iterate through each of the other objects and see if there is an
                    //intersection between the shadow ray (a vector connection our computed intersection_point
                    //and the light) and that object. If there is, then this pixel should be in shadow
                    for(int i = 0; i < scene_objects.size(); i++) {
                        //for each object first construct the shadow ray
                        Vec3 shadow_ray = lights[l].getPosition() - intersection_point;
                        shadow_ray.normalize();
                        float x1, x2;

                        if (isSphere(scene_objects[i]) && scene_objects[i]->getPosition() != s.getPosition()) {
                            //if the object is a sphere we must solve a quadratic to find the intersection of the shadow ray with it
                            float quad_a = shadow_ray.square();
                            Vec3 origin_to_center =
                                    intersection_point - dynamic_cast<Sphere *>(scene_objects[i])->getPosition();
                            float quad_b = 2 * shadow_ray.dot(origin_to_center);
                            float radius = dynamic_cast<Sphere *>(scene_objects[i])->getRadius();
                            float quad_c = origin_to_center.square() - radius * radius;
                            float x1, x2;
                            if (quadratic_solve(quad_a, quad_b, quad_c, x1, x2)) {
                                red = 0.5 * red;
                                blue = 0.5 * blue;
                                green = 0.5 * green;
                            }
                        }
                    }


                    //before proceeding make sure that the values are not greater than 1
                    clamp(red, 0, 1);
                    clamp(green, 0, 1);
                    clamp(blue, 0, 1);
                }

                image(ray.getPixel().x, ray.getPixel().y, 0, 0) = red*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 1) = green*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 2) = blue*255;
            }
            depth_buffer.shift();
        }
    }

    std::cout << "Sphere Processing Complete." << std::endl;
}

void RayTracer::trace(Plane p)
{
    //this will do ray tracing for a plane p defined by its center point p0 and its normal n
    //the intersection point of a ray with this plane (assuming it exists) will be called p.
    //since it is on the plane, we can take the difference between this point and the origin of the plane
    //this will give us a vector that lies on the plane and is therefore perpendicular to the normal
    //this means that the dot product of this vector and the plane's normal is 0
    //this gives us the following equation: (p-p0).n = 0
    //Since we can also define the point p as a an extension of the ray that we are dealing with, we can write:
    //(O+tD) = p Where O is the origin of the ray (the camera position) and D is it's direction, and t is a jump that
    //we will solve for. We can substitute this into the first equation to get:
    //(O + tD - p0).n = 0
    //O.n + tD.n - p0.n = 0
    //isolating t we get:
    //tD.n = (p0.n - O.n)
    //t = ((p0 - O).n)/(D.n)
    //we now have everything we need to determine the intersection

    std::cout << "Processing Plane..." << std::endl;
    int view_width = camera.getViewWidth();
    int view_height = camera.getViewHeight();
    float t; //the solution to the plane intersection
    Ray ray;
    depth_buffer.reset();

    for(int x = 0; x < view_width; x++)
    {
        for(int y = 0; y < view_height; y++)
        {
            //iterate over each "pixel" that the camera can see and set the ray for that pixel
            ray.setRay(Vec3(view_width/2-x, y - view_height/2, camera.getFocalLength()));
            ray.setPixel(Pixel(x, y));
            ray.getRay().normalize();

            Vec3 ray_direction = ray.getRay();

            if(plane_solve(camera.getPosition(), ray_direction, p, t))
            {
                //if we have a solution, we need to compute the lighting for that point
                //this needs to be done for every light in our vector of lights

                //the three color channels
                float red = 0;
                float green = 0;
                float blue = 0;

                //for each light we need to get the direction from the light to the intersection points
                //in order to do this, we first need to find those intersection points
                Vec3 intersection_point = getPlaneIntersection(camera.getPosition(), ray_direction, t);

                //now that we have the intersection points, we need to compute the normals at this point
                //for the sphere, this is done by taking the difference between the point and the center of the
                //sphere and then normalizing it
                Vec3 normal = p.getNormal();
                normal.normalize();

                //we need to check if the z value of this intersection is closer than the closest depth recorded
                //in the depth buffer

                if((camera.getPosition() - intersection_point).length() >
                   depth_buffer.getCurrentDepth())
                {
                    //if the depth is greater, we don't want to draw that point and so we should break
                    continue;
                }

                else
                {
                    //if the  depth of the intersection is closer than what is in the depth buffer, then we color
                    //in the pixel
                    //update the depth buffer
                    depth_buffer.setCurrentDepth((camera.getPosition() - intersection_point).length());
                }

                for(int l = 0; l < lights.size(); l++)
                {


                    //we only want to keep the closest intersection point so we don't draw for no reason

                    //now we need to calculate the diffuse strength for each of these points
                    //the diffuse strength is the dot product of the light direction and the surface normal
                    //if the light direction is parallel to the normal this is highest intensity = 1
                    //if it is perpendicular then the intensity is 0
                    Vec3 light_direction = lights[l].getPosition() - intersection_point;
                    light_direction.normalize();
                    float diffuse_strength = light_direction.dot(normal);
                    clamp(diffuse_strength, 0, 1);

                    //the next step is to calculate the specular strength
                    //in order to do this, we need to take the dot of the reflected light vector about the normal
                    //and the view vector, which is the ray direction and raise it to the shininess
                    Vec3 reflection = light_direction.reflect(normal);
                    reflection.normalize();
                    ray_direction.normalize();
                    float spec_strength = ray_direction.dot(reflection);
                    clamp(spec_strength, 0, 1);
                    spec_strength = pow(spec_strength, p.getShininess());

                    //now we calculate the color of the pixel
                    red += ambient_coefficient*p.getAmbientColor().x
                           + diffuse_coefficient*diffuse_strength*p.getDiffuseColor().x
                           + specular_coefficient*spec_strength*p.getSpecularColor().x;
                    green += ambient_coefficient*p.getAmbientColor().y
                             + diffuse_coefficient*diffuse_strength*p.getDiffuseColor().y
                             + specular_coefficient*spec_strength*p.getSpecularColor().y;
                    blue += ambient_coefficient*p.getAmbientColor().z
                            + diffuse_coefficient*diffuse_strength*p.getDiffuseColor().z
                            + specular_coefficient*spec_strength*p.getSpecularColor().z;

                    //now that we have computed the colors from the lighting we need to check if this pixel should be
                    //in shadow. This will be the case if there is another object between it and the light.
                    //therefore we need to iterate through each of the other objects and see if there is an
                    //intersection between the shadow ray (a vector connection our computed intersection_point
                    //and the light) and that object. If there is, then this pixel should be in shadow
                    for(int i = 0; i < scene_objects.size(); i++)
                    {
                        //for each object first construct the shadow ray
                        Vec3 shadow_ray = lights[l].getPosition() - intersection_point;
                        shadow_ray.normalize();
                        float x1, x2;
                        if(isSphere(scene_objects[i]))
                        {
                            //if the object is a sphere we must solve a quadratic to find the intersection of the shadow ray with it
                            float quad_a = shadow_ray.square();
                            Vec3 origin_to_center = intersection_point - dynamic_cast<Sphere*>(scene_objects[i])->getPosition();
                            float quad_b = 2*shadow_ray.dot(origin_to_center);
                            float radius = dynamic_cast<Sphere*>(scene_objects[i])->getRadius();
                            float quad_c = origin_to_center.square() - radius*radius;
                            float x1, x2;
                            if(quadratic_solve(quad_a, quad_b, quad_c, x1, x2))
                            {
                                red = 0.5*red;
                                blue = 0.5*blue;
                                green = 0.5*green;
                            }
                        }

                    }

                    //before proceeding make sure that the values are not greater than 1
                    clamp(red, 0, 1);
                    clamp(green, 0, 1);
                    clamp(blue, 0, 1);
                }

                image(ray.getPixel().x, ray.getPixel().y, 0, 0) = red*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 1) = green*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 2) = blue*255;
            }

            depth_buffer.shift(); //move to the next element in the depth buffer
        }
    }
    std::cout << "Plane Processing Complete." << std::endl;
}

bool RayTracer::plane_solve(Vec3& ray_origin, Vec3& ray_direction, Plane& plane, float& t)
{
    //this will solve the plane equation derived in the plane tracer function: t = ((p0 - O).n)/(D.n)
    //t is the solution which will be returned if it exists

    //first let us calculate the bottom portion
    float bottom = ray_direction.dot(plane.getNormal());
    //now if the bottom is very close to zero, this means that we do not have a solution and we should return false
    if(bottom < 1e-6)
        return false;

    //otherwise we can solve the equation and place the solution in t
    float top = (plane.getPosition() - ray_origin).dot(plane.getNormal());
    t = top/bottom;
    return true;

}

bool RayTracer::quadratic_solve(float a, float b, float c, float& x1, float& x2)
{
    //the solutions x1 and x2 are floats that must be multiplied by the direction of the ray and added to its origin
    //the camera position, in order to get the intersection point for the sphere

    float disc = discriminant(a, b, c);
    //if the discriminant is less than 0, this means there are no solutions and we should return false
    if(disc < 1e-6)
        return false;

    else if(disc == 1e-6)
    {
        //if the discriminant is zero, then we should calculate the one solution which is given by -b/2a
        //and assign to each solution and return true
        x1, x2 = -0.5*b/a;
        return true;
    }

    else
    {
        //if we are here it means that the equation has two solutions and the discriminant was positive
        x1 = (-b + sqrt(disc))/(2*a);
        x2 = (-b - sqrt(disc))/(2*a);

        //we will also test to see which is larger and place the largest value in x2

        if(x1 > x2)
        {
            float temp = x2;
            x2 = x1;
            x1 = temp;
        }

        return true;
    }
}

float RayTracer::discriminant(float a, float b, float c)
{
    return b*b - 4*a*c;
}

Vec3 RayTracer::getSphereIntersection(Vec3& ray_origin, Vec3& ray_direction, float intersection_jump_1, float intersection_jump_2)
{
    //this calculates the intersection point for a sphere based on the ray origin, its direction and the intersection
    //jump, which is a solution to the quadratic equation.
    Vec3 ray_jump_1 = ray_direction*intersection_jump_1;
    Vec3 ray_jump_2 = ray_direction*intersection_jump_2;

    if((ray_origin+ray_jump_1).length() < (ray_origin+ray_jump_2).length())
        return ray_origin + ray_jump_1;
    else
        return ray_origin + ray_jump_2;
}

Vec3 RayTracer::getPlaneIntersection(Vec3& ray_origin, Vec3& ray_direction, float intersection_jump)
{
    Vec3 ray_jump = ray_direction*intersection_jump;
    return ray_origin + ray_jump;
}

void RayTracer::display_image()
{
    image.display("Scene");
}

void RayTracer::save_image(const char *filepath)
{
    image.save(filepath);
}

void RayTracer::clamp(float& f, float low_bound, float high_bound)
{
    //check for NaN
    if(f != f)
    {
        f = 0;
        return;
    }

    if(f < low_bound)
        f = low_bound;

    if(f > high_bound)
        f = high_bound;
}

bool RayTracer::isPlane(SceneObject *o)
{
    if(dynamic_cast<Plane*>(o))
        return true;

    return false;
}

bool RayTracer::isSphere(SceneObject *o)
{
    if(dynamic_cast<Sphere*>(o))
        return true;

    return false;
}