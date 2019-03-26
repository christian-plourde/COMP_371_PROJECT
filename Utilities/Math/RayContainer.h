#ifndef RAY_CONTAINER_H
#define RAY_CONTAINER_H

#include <vector>
#include "Vectors.h"

#include "Ray.h"

class RayContainer
{
    //this class exists to hold all the rays from the ray tracer in a convenient way
    private:
        std::vector<Ray> rays;
    public:
        RayContainer();
        inline std::vector<Ray> getRays(){return rays;}
        int size;
        void addRay(Vec3 v, Pixel p);
        friend std::ostream& operator<<(std::ostream& os, RayContainer container);
};

#endif