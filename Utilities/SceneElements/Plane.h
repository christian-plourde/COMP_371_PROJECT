#ifndef COMP_371_PROJECT_PLANE_H
#define COMP_371_PROJECT_PLANE_H

#include "../Math/Vectors.h"

class Plane
{
    private:
        Vec3 normal;
        Vec3 position;
        Vec3 ambient_color;
        Vec3 diffuse_color;
        Vec3 specular_color;
        float shininess;

    public:
        Plane();
        ~Plane();
        inline void setNormal(Vec3 n){normal = n;}
        inline void setPosition(Vec3 p){position = p;}
        inline void setAmbientColor(Vec3 c){ambient_color = c;}
        inline void setDiffuseColor(Vec3 c){diffuse_color = c;}
        inline void setSpecularColor(Vec3 c){specular_color = c;}
        inline void setShininess(float f){shininess = f;}
        inline Vec3& getNormal(){return normal;}
        inline Vec3& getPosition(){return position;}
        inline Vec3& getAmbientColor(){return ambient_color;}
        inline Vec3& getDiffuseColor(){return diffuse_color;}
        inline Vec3& getSpecularColor(){return specular_color;}
        inline float getShininess(){return shininess;}
};

#endif