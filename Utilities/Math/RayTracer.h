#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "../SceneElements/Camera.h"
#include "RayContainer.h"
#include "../SceneElements/Sphere.h"
#include "../../Libraries/CImg.h"

class RayTracer
{
    private:
        Camera camera; //the ray tracer needs to know the position of the camera.
        RayContainer rays;
        cimg_library::CImg<unsigned char> image;
        float discriminant(float a, float b, float c); //calculate discriminant for the quadratic equation in trace method

    public:
        RayTracer(Camera c);
        inline Camera getCamera(){return camera;}
        inline void setCamera(Camera c){camera = c;}
        inline RayContainer getRays(){return rays;}
        void trace(Sphere s); //will do ray tracing for that sphere

};

#endif