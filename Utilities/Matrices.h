#ifndef MATRICES_H
#define MATRICES_H

#include "Vectors.h"

class Mat3
{
    //a 3x3 matrix
    //there are 9 entries so we need threee vec3's
    private:
        Vec3 row_0;
        Vec3 row_1;
        Vec3 row_2;

    public:
        Mat3(); //creates an indentity matrix
        friend std::ostream& operator<<(std::ostream& os, Mat3& matrix);
        Vec3& operator[](int i);
};

#endif