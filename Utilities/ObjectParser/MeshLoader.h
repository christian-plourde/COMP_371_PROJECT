#ifndef COMP_371_PROJECT_MESHLOADER_H
#define COMP_371_PROJECT_MESHLOADER_H

#include <iostream>
#include <string>
#include "../SceneElements/Mesh.h"
#include <vector>
#include "../Math/Vectors.h"
#include <fstream>
#include "MeshFace.h"

class MeshLoader
{
    public:
        MeshLoader(Mesh mesh);
        ~MeshLoader();
        friend std::ostream& operator<<(std::ostream& os, MeshLoader& mesh_loader);
        bool load();
        inline void setDirectory(std::string dir){mesh_directory = dir;}
        inline std::vector<MeshFace> getMeshFaces(){return mesh_faces;}

    private:
        std::string mesh_directory;
        Mesh mesh;
        std::vector<Vec3> vertices;
        std::vector<Vec3> normals;
        std::vector<MeshFace> mesh_faces;

};

#endif
