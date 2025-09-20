#ifndef HITTABLE_H
#define HITTABLE_H

#include <optional>

#include "ray.h"
#include "interval.h"
#include "hit_record.h"

class hittable {
    public:
        virtual ~hittable() = default;
        virtual std::optional<hit_record> hit(const ray& ray, const interval& interval) const = 0;
};

#endif
