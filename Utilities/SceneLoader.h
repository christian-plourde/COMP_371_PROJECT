#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "Plane.h"
#include "Sphere.h"

class SceneLoader
{
    private:
        Camera camera;
        std::vector<Light> lights;
        Mesh mesh;
        Plane plane;
        std::vector<Sphere> spheres;
        int object_count;
        const char* filename;

    public:
        SceneLoader();
        ~SceneLoader();
        bool loadScene();
        inline void setFilePath(const char* file){filename = file;}
        inline const char* getFilePath(){return filename;}
};

#endif