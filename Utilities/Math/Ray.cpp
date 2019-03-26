#include "Ray.h"

Pixel::Pixel()
{
    x=0;
    y=0;
}

Pixel::Pixel(int x, int y)
{
    this->x = x;
    this->y = y;
}

Ray::Ray()
{

}

Ray::Ray(Vec3 ray, Pixel pixel)
{
    this->ray = ray;
    this->pixel = pixel;
}

std::ostream& operator<<(std::ostream& os, Pixel p)
{
    os << "<" << p.x << ", " << p.y << ">" << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, Ray ray)
{
    os << ray.ray << " " << ray.pixel << std::endl;
    return os;
}