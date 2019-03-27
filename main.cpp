#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Math/RayTracer.h"

int main()
{
    SceneLoader loader;

    loader.setFilePath("../scenes/scene2.txt");
    loader.loadScene();

    RayTracer tracer(loader.getCamera());
    tracer.setLights(loader.getLights());
    tracer.trace(loader.getPlane());
    for(int i = 0; i<loader.getSpheres().size(); i++)
    {
        tracer.trace(loader.getSpheres()[i]);
    }
    tracer.display_image();
    return 0;
}