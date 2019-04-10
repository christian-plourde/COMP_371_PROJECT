#ifndef MESH_H
#define MESH_H

#include "../Math/Vectors.h"
#include "SceneObject.h"

class Mesh : public SceneObject
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
        inline const char* getFileName(){return filename;}
};

#endif