#include "Vectors.h"
#include <cmath>

Vec2::Vec2()
{
    x = 0.0;
    y = 0.0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2::Vec2(float n)
{
    x = n;
    y = n;
}

float Vec2::operator[](int i)
{
    if(i > 1 || i < 0)
        return x;

    if(i == 0)
        return x;

    if(i == 1)
        return y;
}

std::ostream& operator<<(std::ostream& os, Vec2 vector)
{
    os << "<" << vector.x << ", " << vector.y << ">";
    return os;
}

float Vec2::dot(Vec2 &vector)
{
    return x*vector.x + y*vector.y;
}

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

Vec4 operator+(Vec4& vec1, Vec4& vec2)
{
    return Vec4(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
}

Vec3 operator+(Vec3& vec1, Vec3& vec2)
{
    return Vec3(vec1.x+vec2.x, vec1.y + vec2.y, vec1.z+vec2.z);
}

Vec3 operator-(Vec3& vec1, Vec3& vec2)
{
    return Vec3(vec1.x-vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

Vec3 operator*(Vec3& vector, float coeff)
{
    return Vec3(coeff*vector.x, coeff*vector.y, coeff*vector.z);
}

float Vec3::length()
{
    return sqrt(x*x + y*y + z*z);
}

float Vec3::square()
{
    //raises the vector to the second power. This is the same as dotting with itself
    return this->dot(*this);
}

void Vec2::normalize()
{
    //to normalize the vector we must first take the sum of squares of all its elements
    float sum_squares = x*x + y*y;
    //then we divide each element by the sqrt of the sum_squares
    x = x/sqrt(sum_squares);
    y = y/sqrt(sum_squares);
}

void Vec3::normalize()
{
    //to normalize the vector we must first take the sum of squares of all its elements
    float sum_squares = x*x + y*y + z*z;
    //then we divide each element by the sqrt of the sum_squares
    x = x/sqrt(sum_squares);
    y = y/sqrt(sum_squares);
    z = z/sqrt(sum_squares);
}

void Vec4::normalize()
{
    //to normalize the vector we must first take the sum of squares of all its elements
    float sum_squares = x*x + y*y + z*z + w*w;
    //then we divide each element by the sqrt of the sum_squares
    x = x/sqrt(sum_squares);
    y = y/sqrt(sum_squares);
    z = z/sqrt(sum_squares);
    w = w/sqrt(sum_squares);
}