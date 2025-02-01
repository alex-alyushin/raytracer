#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(radius) {}

        // todo: distance to hit point
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            auto origin = r.origin();
            auto direction = r.direction();

            auto w = center - origin;
            auto h = cross(w, unit_vector(direction)).length();

            if (h <= radius) {
                return true;
            }

            return false;
        }

    private:
        point3 center;
        double radius;
};

#endif
