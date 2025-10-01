#ifndef RAY_H
#define RAY_H

#include "vec.h"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec& direction)
            : orig(origin)
            , dir(unit_vector(direction)) {}

        const point3& origin() const {
            return orig;
        }

        const vec& direction() const {
            return dir;
        }

        point3 at(double t) const {
            return orig + t * dir;
        }

    private:
        point3 orig;
        vec dir;
};

#endif
