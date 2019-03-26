#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Math/RayTracer.h"

int main()
{
    SceneLoader loader;

    loader.setFilePath("../scenes/scene2.txt");
    loader.loadScene();

    RayTracer tracer(loader.getCamera()); //doing this will add all the rays that we need

    tracer.trace(loader.getSpheres()[0]);
    tracer.trace(loader.getSpheres()[1]);
    tracer.trace(loader.getSpheres()[2]);
    tracer.display_image();

    return 0;
}