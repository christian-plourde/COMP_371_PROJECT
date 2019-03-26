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
            rays.addRay(Vec3(x-view_width/2, view_height/2 - y, camera.getFocalLength()), Pixel(x, y));
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

    std::cout << "Creating Image: " << camera.getViewWidth() << "x" << camera.getViewHeight() << std::endl;
    std::cout << "Number of rays to process: " << rays.size << std::endl;

    for(int i = 0; i<rays.size; i++)
    {
        if(i != 0 && i%5000 == 0)
            std::cout << i << " rays processed." << std::endl;

        float disc = discriminant(rays.getRays()[i].getRay().square(), 2*rays.getRays()[i].getRay().dot(OtoC), OtoC.square() - R*R);
        if(disc > 0)
        {
            image(rays.getRays()[i].getPixel().x, rays.getRays()[i].getPixel().y, 0, 0) = amb_color.x;
            image(rays.getRays()[i].getPixel().x, rays.getRays()[i].getPixel().y, 0, 1) = amb_color.y;
            image(rays.getRays()[i].getPixel().x, rays.getRays()[i].getPixel().y, 0, 2) = amb_color.z;
        }
    }

    image.display("Scene");
}

float RayTracer::discriminant(float a, float b, float c)
{
    return b*b - 4*a*c;
}
