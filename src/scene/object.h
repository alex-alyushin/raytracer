#ifndef OBJECT_H
#define OBJECT_H

#include <optional>

#include "ray.h"
#include "interval.h"
#include "intersection.h"

class object {
    public:
        virtual ~object() = default;
        virtual bool hit(
            const ray& ray,
            const interval& interval,
            intersection& intersection
        ) const = 0;
};

#endif
