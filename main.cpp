#include <iostream>
#include "Utilities/SceneLoader.h"
#include "Utilities/Math/Matrices.h"
#include "Libraries/CImg.h"

int main()
{
    SceneLoader loader;

    loader.setFilePath("../scenes/scene1.txt");
    loader.loadScene();

    std::cout << "Camera Position: " << loader.getCamera().getPosition() << std::endl;
    std::cout << "Camera FOV: " << loader.getCamera().getFOV() << std::endl;
    std::cout << "Camera Focal Length: " << loader.getCamera().getFocalLength() << std::endl;

    std::cout << loader.getCamera().getViewHeight() << std::endl;
    std::cout << loader.getCamera().getViewWidth() << std::endl;

    cimg_library::CImg<unsigned char> img(640, 400, 1, 3);
    img.fill(0);
    for(int i = 0; i < img.width(); i++)
    {
        for(int j = 0; j < img.height(); j++)
        {
            if(i % 4 == 0)
                img(i, j, 0, 0) = 255;
        }
    }
    img.display("test");

    return 0;
}