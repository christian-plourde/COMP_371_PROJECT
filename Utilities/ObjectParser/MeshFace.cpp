#include "MeshFace.h"

MeshFace::MeshFace()
{

}

MeshFace::~MeshFace() {}

void MeshFace::setVertices(Vec3 v1, Vec3 v2, Vec3 v3)
{
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
}

void MeshFace::setIndices(int v1, int v2, int v3)
{
    vertex_indices[0] = v1;
    vertex_indices[1] = v2;
    vertex_indices[2] = v3;
}

void MeshFace::setVertices(std::vector<Vec3> vertices)
{
    //this will set the vertices from the passed vector based on the indices that we have stored

    this->vertices[0] = vertices[vertex_indices[0] - 1];
    this->vertices[1] = vertices[vertex_indices[1] - 1];
    this->vertices[2] = vertices[vertex_indices[2] - 1];

    //we need to also set the normal
    Vec3 AB = (this->vertices[0] - this->vertices[1]);
    Vec3 AC = (this->vertices[0] - this->vertices[2]);
    normal = AB*AC;
    normal.normalize();
}

std::ostream& operator<<(std::ostream& os, MeshFace& meshFace)
{
    os << "Mesh Face: " << std::endl << "Vertex: " << meshFace.vertices[0] << std::endl << "Vertex: " <<
    meshFace.vertices[1]
    << std::endl << "Vertex: " << meshFace.vertices[2] << std::endl << "Normal: " << meshFace.normal;
    return os;
}

float MeshFace::area()
{
    //this will return the area of the triangle
    //to do this, we compute the normal and return half its length
    Vec3 AB = (this->vertices[0] - this->vertices[1]);
    Vec3 AC = (this->vertices[0] - this->vertices[2]);
    normal = AB*AC;
    return 0.5*normal.length();
}

