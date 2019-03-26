#include "RayTracer.h"

RayTracer::RayTracer(Camera c)
{
    image = cimg_library::CImg<unsigned char>(300, 300, 1, 3);
    image.fill(0);

    camera = c;
    //now we need to add the rays to our ray container
    //we need to do this for each pixel that the camera can see.
    //therefore we need the view width and height of the camera
    int view_width = 300;
    int view_height = 300;

    //the top left corner of the camera view is at x = -view_width/2 and y = view_height/2

    for(int x = 0; x < view_width; x++)
    {
        for(int y = 0; y < view_height; y++)
        {
            //iterate over each "pixel" that the camera can see and set the ray for that pixel
            rays.addRay(Vec3(x-view_width/2, y+view_height/2, camera.getFocalLength()), Pixel(x, y));
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

    for(int i = 0; i<rays.size; i++)
    {
        //for each ray we need to get the discriminant for the quadratic equation and check it's sign
        Vec3 D = rays.getRays()[i].getRay();

        float disc = discriminant(D.square(), 2*D.dot(OtoC), (OtoC).square()-R*R);

        std::cout << "Ray " << i + 1 << " of " << rays.size <<  " Discriminant: " << disc << std::endl;

        if(disc > 0)
        {
            image(rays.getRays()[i].getPixel().x, rays.getRays()[i].getPixel().y, 0, 0) = 255;
        }
    }

    image.display("Scene");
}

float RayTracer::discriminant(float a, float b, float c)
{
    return b*b - 4*a*c;
}
