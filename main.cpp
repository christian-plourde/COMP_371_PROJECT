#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Math/RayTracer.h"

int main()
{
    SceneLoader loader;

    loader.setFilePath("../scenes/scene1.txt");
    loader.loadScene();

    RayTracer tracer(loader.getCamera()); //doing this will add all the rays that we need
    tracer.trace(loader.getSpheres()[0]);

    return 0;
}