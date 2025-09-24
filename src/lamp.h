#ifndef LAMP_H
#define LAMP_H

#include "ray.h"

class lamp {
    public:
        point3 position;
        color3 intensity;

        lamp(const point3& position, const color3& intensity)
            : position(position)
            , intensity(intensity) {}
};

#endif
