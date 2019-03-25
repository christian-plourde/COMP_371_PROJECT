#ifndef COMP_371_PROJECT_VECTORS_H
#define COMP_371_PROJECT_VECTORS_H

#include <iostream>

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
        friend std::ostream& operator<<(std::ostream& os, Vec3& vector);

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
    friend std::ostream& operator<<(std::ostream& os, Vec4& vector);
};

#endif
