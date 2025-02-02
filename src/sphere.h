#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(radius) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            auto origin = r.origin();
            auto direction = r.direction();

            auto w = center - origin;
            auto h = cross(w, unit_vector(direction)).length();

            if (h <= radius) {
                rec.t = std::sqrt(w.length_squared() - h * h) - std::sqrt(radius * radius - h * h);

                return true;
            }

            return false;
        }

    private:
        point3 center;
        double radius;
};

#endif
