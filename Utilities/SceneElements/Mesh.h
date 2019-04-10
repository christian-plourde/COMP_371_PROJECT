#ifndef MESH_H
#define MESH_H

#include "../Math/Vectors.h"
#include "SceneObject.h"
#include "../ObjectParser/MeshFace.h"
#include <vector>

class Mesh : public SceneObject
{
    private:
        const char* filename;
        Vec3 ambient_color;
        Vec3 diffuse_color;
        Vec3 specular_color;
        float shininess;
        std::vector<MeshFace> mesh_faces; //this will hold each face of the mesh that we need to trace

    public:
        Mesh();
        ~Mesh();
        inline void setFilePath(const char* filepath){filename = filepath;}
        inline const char* getFileName(){return filename;}
        inline std::vector<MeshFace> getMeshFaces(){return mesh_faces;}
        inline void setMeshFaces(std::vector<MeshFace> faces){mesh_faces = faces;}
};

#endif