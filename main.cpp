#include <iostream>
#include "Utilities/Camera.h"

int main() {
    Camera camera;
    Vec3 pos(1.2,2,3);
    camera.setPosition(pos);
    std::cout << camera.getPosition() << std::endl;

    return 0;
}