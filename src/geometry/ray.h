#ifndef RAY_H
#define RAY_H

#include "vec.h"
#include "object_counter.h"

class ray {
    public:
        DECLARE_OBJECT_COUNTER()

        ray() {
            INCREMENT_OBJECT_COUNTER();
        }

        ray(const point3& origin, const vec& direction)
            : orig(origin)
            , dir(unit_vector(direction)) {
                INCREMENT_OBJECT_COUNTER();
            }

        ~ray() {
            DECREMENT_OBJECT_COUNTER();
        }

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

DEFINE_OBJECT_COUNTER(ray)

#endif
