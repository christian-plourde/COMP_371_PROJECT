#include "Matrices.h"

Mat3::Mat3()
{
    row_0.x = 1;
    row_1.y = 1;
    row_2.z = 1;
}

std::ostream& operator<<(std::ostream& os, Mat3& matrix)
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

