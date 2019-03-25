#include "Matrices.h"

Mat3::Mat3()
{
    row_0.x = 1;
    row_1.y = 1;
    row_2.z = 1;
}

Mat3::Mat3(Vec3 row1, Vec3 row2, Vec3 row3)
{
    row_0 = row1;
    row_1 = row2;
    row_2 = row3;
}

std::ostream& operator<<(std::ostream& os, Mat3 matrix)
{
    os << "| " << matrix.row_0.x << " " << matrix.row_0.y << " " << matrix.row_0.z << " |" << std::endl;
    os << "| " << matrix.row_1.x << " " << matrix.row_1.y << " " << matrix.row_1.z << " |" << std::endl;
    os << "| " << matrix.row_2.x << " " << matrix.row_2.y << " " << matrix.row_2.z << " |" << std::endl;
    return os;
}

Vec3& Mat3::operator[](int i)
{
    if(i > 2 || i < 0)
        return row_0;

    if(i == 0)
        return row_0;

    if(i == 1)
        return row_1;

    if(i == 2)
        return row_2;
}

Mat4::Mat4()
{
    row_0.x = 1;
    row_1.y = 1;
    row_2.z = 1;
    row_3.w = 1;
}

Mat4::Mat4(Vec4 row1, Vec4 row2, Vec4 row3, Vec4 row4)
{
    row_0 = row1;
    row_1 = row2;
    row_2 = row3;
    row_3 = row4;
}

std::ostream& operator<<(std::ostream& os, Mat4 matrix)
{
    os << "| " << matrix.row_0.x << " " << matrix.row_0.y << " " << matrix.row_0.z << " " << matrix.row_0.w << " |" << std::endl;
    os << "| " << matrix.row_1.x << " " << matrix.row_1.y << " " << matrix.row_1.z << " " << matrix.row_1.w << " |" << std::endl;
    os << "| " << matrix.row_2.x << " " << matrix.row_2.y << " " << matrix.row_2.z << " " << matrix.row_2.w << " |" << std::endl;
    os << "| " << matrix.row_3.x << " " << matrix.row_3.y << " " << matrix.row_3.z << " " << matrix.row_3.w << " |" << std::endl;

    return os;
}

Vec4& Mat4::operator[](int i)
{
    if(i > 3 || i < 0)
        return row_0;

    if(i == 0)
        return row_0;

    if(i == 1)
        return row_1;

    if(i == 2)
        return row_2;

    if(i == 3)
        return row_3;
}

Vec3 operator*(Mat3& matrix, Vec3& vector)
{
    //store the new values for the output vector
    float new_x = 0;
    float new_y = 0;
    float new_z = 0;

    new_x = matrix[0].x*vector.x + matrix[0].y*vector.y + matrix[0].z*vector.z;
    new_y = matrix[1].x*vector.x + matrix[1].y*vector.y + matrix[1].z*vector.z;
    new_z = matrix[2].x*vector.x + matrix[2].y*vector.y + matrix[2].z*vector.z;

    return Vec3(new_x, new_y, new_z);
}

Vec4 operator*(Mat4& matrix, Vec4& vector)
{
    float new_x;
    float new_y;
    float new_z;
    float new_w;

    new_x = matrix[0].x*vector.x + matrix[0].y*vector.y + matrix[0].z*vector.z + matrix[0].w*vector.w;
    new_y = matrix[1].x*vector.x + matrix[1].y*vector.y + matrix[1].z*vector.z + matrix[1].w*vector.w;
    new_z = matrix[2].x*vector.x + matrix[2].y*vector.y + matrix[2].z*vector.z + matrix[2].w*vector.w;
    new_w = matrix[3].x*vector.x + matrix[3].y*vector.y + matrix[3].z*vector.z + matrix[3].w*vector.w;

    return Vec4(new_x, new_y, new_z, new_w);
}

Mat3 operator*(Mat3& matrix1, Mat3& matrix2)
{
    //we will store all the new entries in here
    Vec3 row0;
    Vec3 row1;
    Vec3 row2;

    Vec3 mat2_col1(matrix2[0].x, matrix2[1].x, matrix2[2].x); //the first column of the second matrix
    Vec3 mat2_col2(matrix2[0].y, matrix2[1].y, matrix2[2].y);
    Vec3 mat2_col3(matrix2[0].z, matrix2[1].z, matrix2[2].z);

    row0 = Vec3(matrix1[0].dot(mat2_col1), matrix1[0].dot(mat2_col2), matrix1[0].dot(mat2_col3));
    row1 = Vec3(matrix1[1].dot(mat2_col1), matrix1[1].dot(mat2_col2), matrix1[1].dot(mat2_col3));
    row2 = Vec3(matrix1[2].dot(mat2_col1), matrix1[2].dot(mat2_col2), matrix1[2].dot(mat2_col3));

    return Mat3(row0, row1, row2);
}

Mat4 operator*(Mat4& matrix1, Mat4& matrix2)
{
    //we will store all the new entries in here
    Vec4 row0;
    Vec4 row1;
    Vec4 row2;
    Vec4 row3;

    Vec4 mat2_col1(matrix2[0].x, matrix2[1].x, matrix2[2].x, matrix2[3].x); //the first column of the second matrix
    Vec4 mat2_col2(matrix2[0].y, matrix2[1].y, matrix2[2].y, matrix2[3].y);
    Vec4 mat2_col3(matrix2[0].z, matrix2[1].z, matrix2[2].z, matrix2[3].z);
    Vec4 mat2_col4(matrix2[0].w, matrix2[1].w, matrix2[2].w, matrix2[3].w);

    row0 = Vec4(matrix1[0].dot(mat2_col1), matrix1[0].dot(mat2_col2), matrix1[0].dot(mat2_col3), matrix1[0].dot(mat2_col4));
    row1 = Vec4(matrix1[1].dot(mat2_col1), matrix1[1].dot(mat2_col2), matrix1[1].dot(mat2_col3), matrix1[1].dot(mat2_col4));
    row2 = Vec4(matrix1[2].dot(mat2_col1), matrix1[2].dot(mat2_col2), matrix1[2].dot(mat2_col3), matrix1[2].dot(mat2_col4));
    row3 = Vec4(matrix1[3].dot(mat2_col1), matrix1[3].dot(mat2_col2), matrix1[3].dot(mat2_col3), matrix1[3].dot(mat2_col4));

    return Mat4(row0, row1, row2, row3);
}
