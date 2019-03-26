#include "Camera.h"
#include <cmath>

Camera::Camera()
{}

Camera::~Camera() {}

float Camera::radians(float deg)
{
    return deg*M_PI/180;
}

float Camera::degrees(float radians)
{
    return 180*radians/M_PI;
}

int Camera::getViewHeight()
{
    //the view height is the focal length times half the tan of fov all multiplied by 2
    return tan(radians(fov/2))*focal_length*2;
}

int Camera::getViewWidth()
{
    return aspect_ratio*getViewHeight();
}

Mat4 Camera::perspective()
{
    Vec4 row_1(1/tan(radians(fov/2)), 0, 0, 0);
    Vec4 row_2(0, 1/tan(radians(fov/2)), 0, 0);
    Vec4 row_3(0, 0, -1, -1);
    Vec4 row_4(0, 0, -1, 0);

    return Mat4(row_1, row_2, row_3, row_4);
}