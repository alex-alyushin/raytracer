#ifndef OBJECT_H
#define OBJECT_H

#include <optional>

#include "ray.h"
#include "interval.h"
#include "intersection.h"

class object {
    public:
        virtual ~object() = default;
        virtual std::optional<intersection> hit(const ray& ray, const interval& interval) const = 0;
};

#endif
