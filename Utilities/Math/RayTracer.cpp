#include "RayTracer.h"

RayTracer::RayTracer(Camera c)
{
    camera = c;
    //now we need to add the rays to our ray container
    //we need to do this for each pixel that the camera can see.
    //therefore we need the view width and height of the camera
    int view_width = camera.getViewWidth();
    int view_height = camera.getViewHeight();

    image = cimg_library::CImg<unsigned char>(view_width, view_height, 1, 3);
    image.fill(0);
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
    Vec3 amb_color(s.getAmbientColor().x*255, s.getAmbientColor().y*255, s.getAmbientColor().z*255);
    float x1, x2; //these will store the solution to the quadratic equation, if there is one
    float a = 0;
    float b = 0;
    float c = 0; //these are the parameters for the quadratic equation we will be solving

    std::cout << "Processing Sphere..." << std::endl;

    int view_width = camera.getViewWidth();
    int view_height = camera.getViewHeight();

    Ray ray;

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

                for(int l = 0; l < lights.size(); l++)
                {
                    //for each light we need to get the direction from the light to the intersection points
                    //in order to do this, we first need to find those intersection points
                    Vec3 ray_direction = ray.getRay();
                    Vec3 intersection_point = getSphereIntersection(camera.getPosition(), ray_direction, x1);

                    //we only want to keep the closest intersection point so we don't draw for no reason
                    //now that we have the intersection points, we need to compute the normals at this point
                    //for the sphere, this is done by taking the difference between the point and the center of the
                    //sphere and then normalizing it
                    Vec3 normal = intersection_point - s.getPosition();
                    normal.normalize();

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
                    spec_strength = pow(spec_strength, s.getShininess());

                    //now we calculate the color of the pixel
                    red += s.getAmbientColor().x + diffuse_strength*s.getDiffuseColor().x + spec_strength*s.getSpecularColor().x;
                    green += s.getAmbientColor().y + diffuse_strength*s.getDiffuseColor().y + spec_strength*s.getSpecularColor().y;
                    blue += s.getAmbientColor().z + diffuse_strength*s.getDiffuseColor().z + spec_strength*s.getSpecularColor().z;

                    //before proceeding make sure that the values are not greater than 1
                    clamp(red, 0, 1);
                    clamp(green, 0, 1);
                    clamp(blue, 0, 1);
                }

                image(ray.getPixel().x, ray.getPixel().y, 0, 0) = red*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 1) = green*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 2) = blue*255;
            }
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
                image(ray.getPixel().x, ray.getPixel().y, 0, 0) = p.getAmbientColor().x*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 1) = p.getAmbientColor().y*255;
                image(ray.getPixel().x, ray.getPixel().y, 0, 2) = p.getAmbientColor().z*255;
            }
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
    if(disc < 0)
        return false;

    else if(disc == 0)
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

Vec3 RayTracer::getSphereIntersection(Vec3& ray_origin, Vec3& ray_direction, float intersection_jump)
{
    //this calculates the intersection point for a sphere based on the ray origin, its direction and the intersection
    //jump, which is a solution to the quadratic equation.
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