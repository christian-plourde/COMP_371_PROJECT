#include "SceneLoader.h"
#include <fstream>
#include <string>

SceneLoader::SceneLoader() {object_count = 0; contains_mesh = false;}

SceneLoader::~SceneLoader() {}

bool SceneLoader::loadScene()
{
    //first declare an input filestream
    std::ifstream input(filename);

    if(input.is_open())
    {
        //we need to read the file line by line
        std::string line; //the current line
        while(std::getline(input, line))
        {
            //the first line of the file should always be the object count so we should assign that first
            sscanf(line.c_str(), "%d", &object_count);

            //next we should look for a camera
            if(line.find("camera") != std::string::npos && line.length() != 0)
            {
                //once we have found a camera, we need to read 4 lines
                for(int i = 0; i < 4; i++)
                {
                    //get the next line
                    std::getline(input, line);

                    //check what is in it
                    if(line.find("pos") != std::string::npos && line.length() != 0)
                    {
                        //if the line contains the position of the camera, this is a vec3
                        Vec3 position;
                        sscanf(line.c_str(), "pos: %f %f %f", &position.x, &position.y, &position.z);
                        camera.setPosition(position);
                    }

                    if(line.find('f') != std::string::npos && line.length() != 0)
                    {
                        //this is the line containing the focal length
                        float focal_length;
                        sscanf(line.c_str(), "f: %f", &focal_length);
                        camera.setFocalLength(focal_length);
                    }

                    if(line.find("fov") != std::string::npos && line.length() != 0)
                    {
                        float fov;
                        sscanf(line.c_str(), "fov: %f", &fov);
                        camera.setFOV(fov);
                    }

                    if(line.find('a') != std::string::npos && line.length() != 0)
                    {
                        float aspect_ratio;
                        sscanf(line.c_str(), "a: %f", &aspect_ratio);
                        camera.setAspectRatio(aspect_ratio);
                    }
                }
            }

            //next we should look for a plane
            if(line.find("plane") != std::string::npos && line.length() != 0)
            {
                //if we have found a plane we have 6 lines to read
                for(int i = 0; i<6; i++)
                {
                    //get the next line
                    std::getline(input, line);

                    //first we look for the normal to the plane, which is a vec3
                    if(line.find("nor") != std::string::npos && line.length() != 0)
                    {
                        //the normal is a vec3
                        Vec3 normal;
                        sscanf(line.c_str(), "nor: %f %f %f", &normal.x, &normal.y, &normal.z);
                        plane.setNormal(normal);
                    }

                    //next we look for the position of the plane
                    if(line.find("pos") != std::string::npos && line.length() != 0)
                    {
                        Vec3 position;
                        sscanf(line.c_str(), "pos: %f %f %f", &position.x, &position.y, &position.z);
                        plane.setPosition(position);
                    }

                    //next we need to find the ambient color
                    if(line.find("amb") != std::string::npos && line.length() != 0)
                    {
                        Vec3 ambient;
                        sscanf(line.c_str(), "amb: %f %f %f", &ambient.x, &ambient.y, &ambient.z);
                        plane.setAmbientColor(ambient);
                    }

                    //now the diffuse color
                    if(line.find("dif") != std::string::npos && line.length() != 0)
                    {
                        Vec3 diffuse;
                        sscanf(line.c_str(), "dif: %f %f %f", &diffuse.x, &diffuse.y, &diffuse.z);
                        plane.setDiffuseColor(diffuse);
                    }

                    //now for the specular color
                    if(line.find("spe") != std::string::npos && line.length() != 0)
                    {
                        Vec3 spec;
                        sscanf(line.c_str(), "spe: %f %f %f", &spec.x, &spec.y, &spec.z);
                        plane.setSpecularColor(spec);
                    }

                    //finally for the shininess coefficient
                    if(line.find("shi") != std::string::npos && line.length() != 0)
                    {
                        float shi;
                        sscanf(line.c_str(), "shi: %f", &shi);
                        plane.setShininess(shi);
                    }
                }
            }

            //next we need to look for a mesh
            if(line.find("mesh") != std::string::npos && line.length() != 0)
            {
                //first set contains_mesh to true
                contains_mesh = true;

                //if we have found a mesh, we have five lines to read
                for(int i = 0; i<5; i++)
                {
                    std::getline(input, line);

                    if(line.find("file") != std::string::npos && line.length() != 0)
                    {
                        char* filepath;
                        filepath = (char*)malloc(200*sizeof(char)); //allocate memory for filepath
                        sscanf(line.c_str(), "file: %s", filepath);
                        mesh.setFilePath(filepath);
                    }

                    //next we need to look for the ambient color
                    if(line.find("amb") != std::string::npos && line.length() != 0)
                    {
                        Vec3 ambient;
                        sscanf(line.c_str(), "amb: %f %f %f", &ambient.x, &ambient.y, &ambient.z);
                        mesh.setAmbientColor(ambient);
                    }

                    //now the diffuse color
                    if(line.find("dif") != std::string::npos && line.length() != 0)
                    {
                        Vec3 diffuse;
                        sscanf(line.c_str(), "dif: %f %f %f", &diffuse.x, &diffuse.y, &diffuse.z);
                        mesh.setDiffuseColor(diffuse);
                    }

                    //now for the specular color
                    if(line.find("spe") != std::string::npos && line.length() != 0)
                    {
                        Vec3 spec;
                        sscanf(line.c_str(), "spe: %f %f %f", &spec.x, &spec.y, &spec.z);
                        mesh.setSpecularColor(spec);
                    }

                    //finally for the shininess coefficient
                    if(line.find("shi") != std::string::npos && line.length() != 0)
                    {
                        float shi;
                        sscanf(line.c_str(), "shi: %f", &shi);
                        mesh.setShininess(shi);
                    }
                }
            }

            //next we need to look for spheres. Since there can be many, we store these spheres in a vector
            if(line.find("sphere") != std::string::npos && line.length() != 0)
            {
                //create a new sphere temporarily
                Sphere sphere;

                //for each sphere that we have found, we have six lines to read
                for(int i = 0; i<6; i++)
                {
                    std::getline(input, line);

                    if(line.find("pos") != std::string::npos && line.length() != 0)
                    {
                        Vec3 position;
                        sscanf(line.c_str(), "pos: %f %f %f", &position.x, &position.y, &position.z);
                        sphere.setPosition(position);
                    }

                    if(line.find("rad") != std::string::npos && line.length() != 0)
                    {
                        float radius;
                        sscanf(line.c_str(), "rad: %f", &radius);
                        sphere.setRadius(radius);
                    }

                    //next we need to look for the ambient color
                    if(line.find("amb") != std::string::npos && line.length() != 0)
                    {
                        Vec3 ambient;
                        sscanf(line.c_str(), "amb: %f %f %f", &ambient.x, &ambient.y, &ambient.z);
                        sphere.setAmbientColor(ambient);
                    }

                    //now the diffuse color
                    if(line.find("dif") != std::string::npos && line.length() != 0)
                    {
                        Vec3 diffuse;
                        sscanf(line.c_str(), "dif: %f %f %f", &diffuse.x, &diffuse.y, &diffuse.z);
                        sphere.setDiffuseColor(diffuse);
                    }

                    //now for the specular color
                    if(line.find("spe") != std::string::npos && line.length() != 0)
                    {
                        Vec3 spec;
                        sscanf(line.c_str(), "spe: %f %f %f", &spec.x, &spec.y, &spec.z);
                        sphere.setSpecularColor(spec);
                    }

                    //finally for the shininess coefficient
                    if(line.find("shi") != std::string::npos && line.length() != 0)
                    {
                        float shi;
                        sscanf(line.c_str(), "shi: %f", &shi);
                        sphere.setShininess(shi);
                    }
                }

                //now that the sphere data is set we should add it to our sphere vector
                spheres.push_back(sphere);

            }

            //finally we need to look for lights. Once again we have many so we place them in a vector
            if(line.find("light") != std::string::npos && line.length() != 0)
            {
                //create a new light temporarily
                Light light;

                //we have 4 lines to read
                for(int i = 0; i<3; i++)
                {
                    std::getline(input, line);

                    if(line.find("pos") != std::string::npos && line.length() != 0)
                    {
                        Vec3 position;
                        sscanf(line.c_str(), "pos: %f %f %f", &position.x, &position.y, &position.z);
                        light.setPosition(position);
                    }

                    //next we need to look for the ambient color
                    if(line.find("amb") != std::string::npos && line.length() != 0)
                    {
                        Vec3 ambient;
                        sscanf(line.c_str(), "amb: %f %f %f", &ambient.x, &ambient.y, &ambient.z);
                        light.setAmbientColor(ambient);
                    }

                    //now the diffuse color
                    if(line.find("dif") != std::string::npos && line.length() != 0)
                    {
                        Vec3 diffuse;
                        sscanf(line.c_str(), "dif: %f %f %f", &diffuse.x, &diffuse.y, &diffuse.z);
                        light.setDiffuseColor(diffuse);
                    }

                    //now for the specular color
                    if(line.find("spe") != std::string::npos && line.length() != 0)
                    {
                        Vec3 spec;
                        sscanf(line.c_str(), "spe: %f %f %f", &spec.x, &spec.y, &spec.z);
                        light.setSpecularColor(spec);
                    }
                }

                //finally we add it to our vector
                lights.push_back(light);
            }
        }

        //make sure input is closed before returning
        input.close();
        //print_data();
        return true;
    }

    //in the case where we failed to open the file we should return false and close the input stream
    input.close();
    return false;
}

void SceneLoader::print_data()
{
    std::cout << "Camera position: " << camera.getPosition() << std::endl;
    std::cout << "Camera focal length: " << camera.getFocalLength() << std::endl;
    std::cout << "Camera fov: " << camera.getFOV() << std::endl;
    std::cout << "Camera aspect ratio: " << camera.getAspectRatio() << std::endl;
    std::cout << "Plane normal: " << plane.getNormal() << std::endl;
    std::cout << "Plane position: " << plane.getPosition() << std::endl;
    std::cout << "Plane ambient color: " << plane.getAmbientColor() << std::endl;
    std::cout << "Plane diffuse color: " << plane.getDiffuseColor() << std::endl;
    std::cout << "Plane specular color: " << plane.getSpecularColor() << std::endl;
    std::cout << "Plane shininess: " << plane.getShininess() << std::endl;
    if(contains_mesh)
    {
        std::cout << "Mesh filepath: " << mesh.getFileName() << std::endl;
        std::cout << "Mesh ambient color: " << mesh.getAmbientColor() << std::endl;
        std::cout << "Mesh diffuse color: " << mesh.getDiffuseColor() << std::endl;
        std::cout << "Mesh specular color: " << mesh.getSpecularColor() << std::endl;
        std::cout << "Mesh shininess: " << mesh.getShininess() << std::endl;
    }
    for(int i = 0; i<spheres.size(); i++)
    {
        std::cout << "Sphere " << i << " position: " << spheres[i].getPosition() << std::endl;
        std::cout << "Sphere " << i << " radius: " << spheres[i].getRadius() << std::endl;
        std::cout << "Sphere " << i << " ambient color: " << spheres[i].getAmbientColor() << std::endl;
        std::cout << "Sphere " << i << " diffuse color: " << spheres[i].getDiffuseColor() << std::endl;
        std::cout << "Sphere " << i << " specular color: " << spheres[i].getSpecularColor() << std::endl;
        std::cout << "Sphere " << i << " shininess: " << spheres[i].getShininess() << std::endl;
    }

    for(int i = 0; i<lights.size(); i++)
    {
        std::cout << "Light " << i << " position: " << lights[i].getPosition() << std::endl;
        std::cout << "Light " << i << " ambient color: " << lights[i].getAmbientColor() << std::endl;
        std::cout << "Light " << i << " diffuse color: " << lights[i].getDiffuseColor() << std::endl;
        std::cout << "Light " << i << " specular color: " << lights[i].getSpecularColor() << std::endl;
    }
}

std::vector<SceneObject*> SceneLoader::getAllObjects()
{
    std::vector<SceneObject*> toReturn;
    toReturn.push_back(&plane);
    for(int i = 0; i < spheres.size(); i++)
    {
        toReturn.push_back(&(spheres[i]));
    }
    return toReturn;
}
