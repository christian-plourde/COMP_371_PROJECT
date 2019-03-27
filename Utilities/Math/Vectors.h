#ifndef COMP_371_PROJECT_VECTORS_H
#define COMP_371_PROJECT_VECTORS_H

#include <iostream>

class Vec2
{
    public:
        float x;
        float y;
        Vec2();
        Vec2(float x, float y);
        Vec2(float n);
        float operator[](int i);
        friend std::ostream& operator<<(std::ostream& os, Vec2 vector);
        float dot(Vec2& vector); //dot product
        void normalize(); //normalizes the vector
};

class Vec3
{
    public:
        float x;
        float y;
        float z;
        Vec3();
        Vec3(float x, float y, float z);
        Vec3(float n);
        float operator[](int i);
        friend std::ostream& operator<<(std::ostream& os, Vec3 vector);
        friend Vec3 operator*(Vec3& vec1, Vec3& vec2); //cross product
        friend Vec3 operator+(Vec3& vec1, Vec3& vec2);
        friend Vec3 operator-(Vec3& vec1, Vec3& vec2);
        friend Vec3 operator*(Vec3& vector, float coeff);
        float length();
        float square();
        float dot(Vec3& vector); //dot product
        void normalize(); //normalizes the vector
};

class Vec4
{
    public:
    float x;
    float y;
    float z;
    float w;
    Vec4();
    Vec4(float x, float y, float z, float w);
    Vec4(float n);
    Vec4(Vec3 v, float n);
    float operator[](int i);
    friend std::ostream& operator<<(std::ostream& os, Vec4 vector);
    float dot(Vec4& vector);
    friend Vec4 operator+(Vec4& vec1, Vec4& vec2);
    void normalize(); //normalizes the vector
};

#endif
