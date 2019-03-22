#include "Vectors.h"

Vec3::Vec3()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3::Vec3(float n)
{
    x = n;
    y = n;
    z = n;
}

std::ostream& operator<<(std::ostream& os, Vec3& vector)
{
    os << "<" << vector.x << ", " << vector.y << ", " << vector.z << ">";
    return os;
}

