#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Matrices.h"

int main()
{
    SceneLoader loader;
    loader.setFilePath("../scenes/scene1.txt");
    loader.loadScene();

    Vec3 vec1(1, 2, 3);
    Vec3 vec2(3, 4, 5);
    std::cout << vec1 << std::endl;
    std::cout << vec2 << std::endl;
    std::cout << vec1*vec2 << std::endl;
    std::cout << vec1.dot(vec2) << std::endl;

    Mat4 mat1(Vec4(1,2,3,4), Vec4(4,5,6,7), Vec4(7,8,9,10), Vec4(10,11,12,13));
    Mat4 mat2(Vec4(1,2,3,4), Vec4(4,5,6,7), Vec4(7,8,9,10), Vec4(10,11,12,13));

    std::cout << mat1*mat2 << std::endl;

    return 0;
}