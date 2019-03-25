#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <vector>
#include "SceneElements/Camera.h"
#include "SceneElements/Light.h"
#include "SceneElements/Mesh.h"
#include "SceneElements/Plane.h"
#include "SceneElements/Sphere.h"

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
        void print_data();

    public:
        SceneLoader();
        ~SceneLoader();
        bool loadScene();
        inline void setFilePath(const char* file){filename = file;}
        inline const char* getFilePath(){return filename;}
        inline Camera& getCamera(){return camera;}
        inline Mesh& getMesh(){return mesh;}
        inline Plane& getPlane(){return plane;}
        inline std::vector<Sphere>& getSpheres(){return spheres;}
        inline std::vector<Light>& getLights(){return lights;}
};

#endif