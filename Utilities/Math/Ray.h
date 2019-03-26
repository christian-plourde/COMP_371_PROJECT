#ifndef RAY_H
#define RAY_H

#include "Vectors.h"

class Pixel
{
    public:
        int x;
        int y;
        Pixel();
        Pixel(int x, int y);
        friend std::ostream& operator<<(std::ostream& os, Pixel p);
};

class Ray
{
    //this class contains a Vec3, which is a ray through a pixel, and the coordinates of that pixel
    private:
        Vec3 ray;
        Pixel pixel;

    public:
        Ray();
        Ray(Vec3 ray, Pixel pixel);
        inline Vec3 getRay(){return ray;}
        inline void setRay(Vec3 r){ray = r;}
        inline Pixel getPixel(){return pixel;}
        inline void setPixel(Pixel p){pixel = p;}
        friend std::ostream& operator<<(std::ostream& os, Ray ray);
};

#endif