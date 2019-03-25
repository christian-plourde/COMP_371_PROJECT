#ifndef SPHERE_H
#define SPHERE_H

#include "Vectors.h"

class Sphere
{
    private:
        Vec3 position;
        float radius;
        Vec3 ambient_color;
        Vec3 diffuse_color;
        Vec3 specular_color;
        float shininess;

    public:
        Sphere();
        ~Sphere();
        inline void setPosition(Vec3 p){position = p;}
        inline void setAmbientColor(Vec3 c){ambient_color = c;}
        inline void setDiffuseColor(Vec3 c){diffuse_color = c;}
        inline void setSpecularColor(Vec3 c){specular_color = c;}
        inline void setShininess(float f){shininess = f;}
        inline void setRadius(float r){radius = r;}
        inline Vec3& getPosition(){return position;}
        inline Vec3& getAmbientColor(){return ambient_color;}
        inline Vec3& getDiffuseColor(){return diffuse_color;}
        inline Vec3& getSpecularColor(){return specular_color;}
        inline float getShininess(){return shininess;}
        inline float getRadius(){return radius;}
};

#endif