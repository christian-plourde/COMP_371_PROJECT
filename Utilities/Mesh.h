#ifndef MESH_H
#define MESH_H

#include "Vectors.h"

class Mesh
{
    private:
        const char* filename;
        Vec3 ambient_color;
        Vec3 diffuse_color;
        Vec3 specular_color;
        float shininess;

    public:
        Mesh();
        ~Mesh();
        inline void setFilePath(const char* filepath){filename = filepath;}
        inline void setAmbientColor(Vec3 c){ambient_color = c;}
        inline void setDiffuseColor(Vec3 c){diffuse_color = c;}
        inline void setSpecularColor(Vec3 c){specular_color = c;}
        inline void setShininess(float f){shininess = f;}
        inline Vec3& getAmbientColor(){return ambient_color;}
        inline const char* getFileName(){return filename;}
        inline Vec3& getDiffuseColor(){return diffuse_color;}
        inline Vec3& getSpecularColor(){return specular_color;}
        inline float getShininess(){return shininess;}
};

#endif