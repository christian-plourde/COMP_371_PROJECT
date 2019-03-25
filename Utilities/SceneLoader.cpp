#include "SceneLoader.h"
#include <fstream>
#include <string>

SceneLoader::SceneLoader() {object_count = 0;}

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
        }

        std::cout << "Camera position: " << camera.getPosition() << std::endl;
        std::cout << "Camera focal length: " << camera.getFocalLength() << std::endl;
        std::cout << "Camera fov: " << camera.getFOV() << std::endl;
        std::cout << "Camera aspect ratio: " << camera.getAspectRatio() << std::endl;

        //make sure input is closed before returning
        input.close();
        return true;
    }

    //in the case where we failed to open the file we should return false and close the input stream
    input.close();
    return false;
}
