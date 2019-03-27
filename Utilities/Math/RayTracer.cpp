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

    //the top left corner of the camera view is at x = -view_width/2 and y = view_height/2

    for(int x = 0; x < view_width; x++)
    {
        for(int y = 0; y < view_height; y++)
        {
            //iterate over each "pixel" that the camera can see and set the ray for that pixel
            rays.addRay(Vec3(view_width/2 - x, y - view_height/2, camera.getFocalLength()), Pixel(x, y));
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
    Vec3 amb_color(s.getAmbientColor().x*255, s.getAmbientColor().y*255, s.getAmbientColor().z*255);
    float x1, x2; //these will store the solution to the quadratic equation, if there is one
    float a = 0;
    float b = 0;
    float c = 0; //these are the parameters for the quadratic equation we will be solving

    std::cout << "Processing Sphere..." << std::endl;
    std::cout << "Number of rays to process: " << rays.size << std::endl;

    for(int i = 0; i<rays.size; i++)
    {
        if(i != 0 && i%1000 == 0)
            std::cout << i << " rays processed." << std::endl;

        //for each ray we are going to have to solve a quadratic equation
        //the parameters are as follows:
        a = rays.getRays()[i].getRay().square();
        b = 2*rays.getRays()[i].getRay().dot(OtoC);
        c = OtoC.square() - R*R;

        if(quadratic_solve(a, b, c, x1, x2))
        {
            image(rays.getRays()[i].getPixel().x, rays.getRays()[i].getPixel().y, 0, 0) = amb_color.x;
            image(rays.getRays()[i].getPixel().x, rays.getRays()[i].getPixel().y, 0, 1) = amb_color.y;
            image(rays.getRays()[i].getPixel().x, rays.getRays()[i].getPixel().y, 0, 2) = amb_color.z;
        }
    }

    std::cout << "Sphere Processing Complete." << std::endl;
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