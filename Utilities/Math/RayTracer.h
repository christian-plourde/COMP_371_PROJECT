#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "../SceneElements/Camera.h"
#include "../SceneElements/Sphere.h"
#include "../SceneElements/Plane.h"
#include "../SceneElements/Light.h"
#include "../../Libraries/CImg.h"
#include "Ray.h"
#include <vector>

class RayTracer
{
    private:
        Camera camera; //the ray tracer needs to know the position of the camera.
        std::vector<Light> lights;
        cimg_library::CImg<unsigned char> image;
        float discriminant(float a, float b, float c); //calculate discriminant for the quadratic equation in trace method
        bool quadratic_solve(float a, float b, float c, float& x1, float& x2); //quadratic equation solver (answer
        //gets stored in x1 and x2)
        bool plane_solve(Vec3& ray_origin, Vec3& ray_direction, Plane& plane, float& t);
        Vec3 getSphereIntersection(Vec3& ray_origin, Vec3& ray_direction, float intersection_jump);
        Vec3 getPlaneIntersection(Vec3& ray_origin, Vec3& ray_direction, float intersection_jump);
        float ambient_coefficient;
        float specular_coefficient;
        float diffuse_coefficient;
        std::vector<SceneObject*> scene_objects;
        Plane plane;
        bool isPlane(SceneObject* o);
        bool isSphere(SceneObject* o);

    public:
        RayTracer(Camera c);
        inline Camera getCamera(){return camera;}
        inline void setCamera(Camera c){camera = c;}
        inline void setLights(std::vector<Light> l){lights = l;}
        void display_image();
        void save_image(const char* filepath);
        void trace(std::vector<SceneObject*> s);
        void trace(Sphere s); //will do ray tracing for that sphere
        void trace(Plane p); //will do ray tracing for a plane
        void clamp(float& f, float low_bound, float high_bound); //clamps the float value passed between the low and high bounds
};

#endif