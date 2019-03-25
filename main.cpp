#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Matrices.h"

int main()
{
    SceneLoader loader;
    loader.setFilePath("../scenes/scene1.txt");
    loader.loadScene();

    Mat3 matrix;
    std::cout << matrix << std::endl;
    std::cout << matrix[0][0] << std::endl;

    return 0;
}