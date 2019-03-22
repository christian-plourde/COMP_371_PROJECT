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
        friend std::ostream& operator<<(std::ostream& os, Vec3& vector);

};

#endif
