#ifndef SPHERE_H
#define SPHERE_H

#include "SceneObject.h"

class Sphere : public SceneObject
{
    private:
        float radius;

    public:
        Sphere();
        ~Sphere();
        inline void setRadius(float r){radius = r;}
        inline float getRadius(){return radius;}
};

#endif