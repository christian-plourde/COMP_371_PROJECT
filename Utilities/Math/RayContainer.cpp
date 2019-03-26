#include "RayContainer.h"

RayContainer::RayContainer()
{
    size = 0;
}

void RayContainer::addRay(Vec3 v, Pixel p)
{
    v.normalize();
    rays.push_back(Ray(v, p));
    size++;
}

std::ostream& operator<<(std::ostream& os, RayContainer container)
{
    for(int i = 0; i<container.rays.size(); i++)
    {
        os << container.rays[i] << std::endl;
    }

    return os;
}

