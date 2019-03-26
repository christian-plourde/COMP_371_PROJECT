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
        bool quadratic_solve(float a, float b, float c, float& x1, float& x2); //quadratic equation solver (answer
        //gets stored in x1 and x2)
        Vec3 getSphereIntersection(Vec3& ray_origin, Vec3& ray_direction, float intersection_jump);

    public:
        RayTracer(Camera c);
        inline Camera getCamera(){return camera;}
        inline void setCamera(Camera c){camera = c;}
        inline RayContainer getRays(){return rays;}
        void display_image();
        void trace(Sphere s); //will do ray tracing for that sphere

};

#endif