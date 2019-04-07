#ifndef COMP_371_PROJECT_PLANE_H
#define COMP_371_PROJECT_PLANE_H

#include "SceneObject.h"

class Plane : public SceneObject
{
    private:
        Vec3 normal;

    public:
        Plane();
        ~Plane();
        inline void setNormal(Vec3 n){normal = n;}
        inline Vec3& getNormal(){return normal;}
};

#endif
