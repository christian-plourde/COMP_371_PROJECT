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
        Mat3(Vec3 row1, Vec3 row2, Vec3 row3);
        friend std::ostream& operator<<(std::ostream& os, Mat3 matrix);
        Vec3& operator[](int i);
        friend Vec3 operator*(Mat3& matrix, Vec3& vector); //matrix vector multiplication
        friend Mat3 operator*(Mat3& matrix1, Mat3& matrix2); //matrix matrix multiplication
};

class Mat4
{
    //a 4x4 matrix
    //there are 16 entries so four vec4's

    private:
        Vec4 row_0;
        Vec4 row_1;
        Vec4 row_2;
        Vec4 row_3;

    public:
        Mat4(); //creates an identity matrix
        Mat4(Vec4 row1, Vec4 row2, Vec4 row3, Vec4 row4);
        friend std::ostream& operator<<(std::ostream& os, Mat4 matrix);
        Vec4& operator[](int i);
        friend Vec4 operator*(Mat4& matrix, Vec4& vector); //matrix vector multiplication
        friend Mat4 operator*(Mat4& matrix1, Mat4& matrix2); //matrix matrix multiplication
        Mat4 operator=(Mat4& matrix);
};

#endif