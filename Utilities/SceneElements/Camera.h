#ifndef COMP_371_PROJECT_CAMERA_H
#define COMP_371_PROJECT_CAMERA_H

#include "../Math/Matrices.h"

class Camera
{
    private:
        Vec3 position; //the position of the camera in x, y, z coordinates
        float fov; //field of view in degrees
        float focal_length; //focal length of the camera (a floating point number)
        float aspect_ratio; //the aspect ration of the camera
        float radians(float deg);
        float degrees(float radians);

    public:
        Camera();
        ~Camera();
        inline void setPosition(Vec3 pos) {position = pos;}
        inline void setFOV(float f) {fov = f;}
        inline void setFocalLength(float f) {focal_length = f;}
        inline void setAspectRatio(float f) {aspect_ratio = f;}
        inline Vec3& getPosition(){return position;}
        inline float getFOV(){return fov;}
        inline float getFocalLength(){return focal_length;}
        inline float getAspectRatio(){return aspect_ratio;}
        int getViewHeight();
        int getViewWidth();
        Mat4 perspective(); //returns a perspective projection matrix based on the camera's properties
};

#endif
