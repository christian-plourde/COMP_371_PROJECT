#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Math/Matrices.h"
//#include "Libraries/CImg.h"

int main()
{
    SceneLoader loader;

    loader.setFilePath("../scenes/scene1.txt");
    loader.loadScene();

    std::cout << "Camera Position: " << loader.getCamera().getPosition() << std::endl;
    std::cout << "Camera FOV: " << loader.getCamera().getFOV() << std::endl;
    std::cout << "Camera Focal Length: " << loader.getCamera().getFocalLength() << std::endl;

    Vec4 sphere_position(loader.getSpheres()[0].getPosition(), 1);

    Mat4 perspective = loader.getCamera().perspective();
    std::cout << perspective << std::endl;
    std::cout << sphere_position << std::endl;
    Vec4 sphere_top(0, loader.getSpheres()[0].getRadius(), 0, 0);
    sphere_top.x = (sphere_position + sphere_top).x;
    sphere_top.y = (sphere_position + sphere_top).y;
    sphere_top.z = (sphere_position + sphere_top).z;
    sphere_top.w = 1;

    Vec2 projected_position((perspective*sphere_position).x, (perspective*sphere_position).y);
    Vec2 projected_top((perspective*sphere_top).x, (perspective*sphere_top).y);
    std::cout << projected_position << std::endl;
    std::cout << projected_top << std::endl;

    /*
    cimg_library::CImg<unsigned char> img(640, 400, 1, 3);
    img.fill(0);
    img(projected_position.x + 640/2, 400/2 - projected_position.y, 0, 0) = 255; //center
    img(projected_top.x + 640/2, 400/2 - projected_top.y, 0, 0) = 255;
    img.display("test");
    */

    return 0;
}