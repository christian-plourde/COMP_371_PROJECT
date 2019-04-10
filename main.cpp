#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Math/RayTracer.h"

int main()
{
    SceneLoader loader;

    loader.setFilePath("../scenes/scene5.txt");
    loader.loadScene();
    loader.print_data();
    RayTracer tracer(loader.getCamera());
    tracer.setLights(loader.getLights());

    std::vector<SceneObject*> objects = loader.getAllObjects();
    tracer.trace(objects);

    tracer.display_image();
    //tracer.save_image("../Images/scene1.bmp");
    return 0;
}