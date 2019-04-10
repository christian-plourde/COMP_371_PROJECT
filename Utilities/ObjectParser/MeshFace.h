#ifndef COMP_371_PROJECT_MESHFACE_H
#define COMP_371_PROJECT_MESHFACE_H

#include "../Math/Vectors.h"
#include <vector>

class MeshFace
{
    //this class is essentially a triangle face of a mesh
    //each face has three vertices and a normal
    public:
        MeshFace();
        ~MeshFace();
        void setVertices(std::vector<Vec3> vertices);
        void setIndices(int v1, int v2, int v3);
        friend std::ostream& operator<<(std::ostream& os, MeshFace& meshFace);
        inline Vec3 getNormal(){return normal;}
        inline Vec3 getFirstVertex(){return vertices[0];}
        inline Vec3 getSecondVertex(){return vertices[1];}
        inline Vec3 getThirdVertex(){return vertices[2];}
        float area();

    private:
        void setVertices(Vec3 v1, Vec3 v2, Vec3 v3);
        Vec3 vertices[3];
        int vertex_indices[3];
        Vec3 normal;
};

#endif
