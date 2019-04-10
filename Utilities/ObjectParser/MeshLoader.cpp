#include "MeshLoader.h"

MeshLoader::MeshLoader(Mesh mesh)
{
    this -> mesh = mesh;
}

MeshLoader::~MeshLoader()
{

}

bool MeshLoader::load()
{
    //if there is no directory set we should return
    if(mesh_directory.length() == 0)
        return false;

    //if there was, we need to first construct the string where the obj file resides
    std::string full_path = mesh_directory + "/" + mesh.getFileName();

    //now that we have the path we need to parse the file and get all our vertices and normals
    std::ifstream input(full_path);

    if(input.is_open())
    {
        //read the file line by line and then close it
        std::string current_line;
        while(std::getline(input, current_line))
        {
            //finding vertices. Find "v" will also work for find "vt" and "vn" so we need to filter out those results
            if(current_line.find("v ") != std::string::npos && current_line.length() != 0 &&
            current_line.find("vt") == std::string::npos && current_line.find("vn") == std::string::npos)
            {
                float vx, vy, vz;
                sscanf(current_line.c_str(), "v %f %f %f", &vx, &vy, &vz);
                vertices.push_back(Vec3(vx, vy, vz));
            }

            //now we need the normals
            if(current_line.find("vn ") != std::string::npos && current_line.length() != 0)
            {
                float vx, vy, vz;
                sscanf(current_line.c_str(), "vn %f %f %f", &vx, &vy, &vz);
                normals.push_back(Vec3(vx, vy, vz));
            }

            //finally we need to put the faces in order
            if(current_line.find("f ") != std::string::npos && current_line.length() != 0)
            {
                int f1, f2, f3, f4, f5, f6, f7, f8, f9;
                sscanf(current_line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9);
                MeshFace mesh_face;
                mesh_face.setIndices(f1, f4, f7);
                mesh_faces.push_back(mesh_face);
            }
        }

        //before returning we should assign the correct vertices in the mesh face by using the indices that we found
        for(int i = 0; i < mesh_faces.size(); i++)
        {
            mesh_faces[i].setVertices(vertices);
        }

        input.close();
        return true;
    }

    //we are here if we failed to open the file
    input.close();
    return false;

}

