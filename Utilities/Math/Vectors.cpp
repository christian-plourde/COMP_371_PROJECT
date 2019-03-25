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

std::ostream& operator<<(std::ostream& os, Vec3 vector)
{
    os << "<" << vector.x << ", " << vector.y << ", " << vector.z << ">";
    return os;
}

float Vec3::operator[](int i)
{
    if(i > 2 || i < 0)
        return x;

    if(i == 0)
        return x;

    if(i == 1)
        return y;

    if(i == 2)
        return z;
}

Vec4::Vec4()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 0.0;
}

Vec4::Vec4(float n)
{
    x = n;
    y = n;
    z = n;
    w = 0.0;
}

Vec4::Vec4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4::Vec4(Vec3 v, float n)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    w = n;
}

std::ostream& operator<<(std::ostream& os, Vec4 vector)
{
    os << "<" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ">";
    return os;
}

float Vec4::operator[](int i)
{
    if(i > 3 || i < 0)
        return x;

    if(i == 0)
        return x;

    if(i == 1)
        return y;

    if(i == 2)
        return z;

    if(i == 3)
        return w;
}

Vec3 operator*(Vec3& vec1, Vec3& vec2)
{
    return Vec3(vec1[1]*vec2[2] - vec1[2]*vec2[1], vec1[2]*vec2[0] - vec1[0]*vec2[2], vec1[0]*vec2[1] - vec1[1]*vec2[0]);
}

float Vec3::dot(Vec3& vector)
{
    return x*vector.x + y*vector.y + z*vector.z;
}

float Vec4::dot(Vec4& vector)
{
    return x*vector.x + y*vector.y + z*vector.z + w*vector.w;
}
