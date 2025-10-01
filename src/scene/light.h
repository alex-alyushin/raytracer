#ifndef LIGHT_H
#define LIGHT_H

#include "ray.h"

class light {
    public:
        point3 position;
        color3 intensity;

        light(const point3& position, const color3& intensity)
            : position(position)
            , intensity(intensity) {}
};

#endif
