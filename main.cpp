#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Math/RayTracer.h"
#include "Utilities/RenderSetupHelper.h"

std::string SCENE_FILE_PATH;
std::string IMAGE_FILE_PATH;

int main()
{
    RenderSetupHelper render_setup;
    render_setup.setup();
    SCENE_FILE_PATH = render_setup.getSceneFilePath();
    IMAGE_FILE_PATH = render_setup.getImageFilePath();

    //examples
    //tracer.save_image("../Images/scene1.bmp");
    //loader.setFilePath("../scenes/scene1.txt");

    SceneLoader loader;

    loader.setFilePath(SCENE_FILE_PATH.c_str());

    loader.loadScene();

    RayTracer tracer(loader.getCamera());
    if(!render_setup.getCastShadows())
        tracer.setCastShadows(false);

    tracer.setLights(loader.getLights());

    std::vector<SceneObject*> objects = loader.getAllObjects();
    tracer.trace(objects);

    tracer.display_image();
    if(render_setup.getSaveImage())
        tracer.save_image(IMAGE_FILE_PATH.c_str());
    return 0;
}