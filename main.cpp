#include <iostream>
#include "Utilities/SceneLoader.h"

int main()
{
    SceneLoader loader;
    loader.setFilePath("../scenes/scene1.txt");
    loader.loadScene();


    return 0;
}