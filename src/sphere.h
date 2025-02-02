#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(radius) {}

        bool hit(const ray& r, interval& rng, hit_record& rec) const override {
            auto origin = r.origin();
            auto direction = r.direction();
            auto h = cross(center - origin, unit_vector(direction)).length();

            if (h <= radius) {
                rec.t = std::sqrt((center - origin).length_squared() - h * h)
                      - std::sqrt(radius * radius - h * h);
                rec.point = r.at(rec.t);
                rec.normal = unit_vector(rec.point - center);

                if (rng.min < 0 || rec.t < rng.min) {
                    rng.min = rec.t;
                }

                if (rng.max < 0 || rec.t > rng.max) {
                    rng.max = rec.t;
                }

                return true;
            }

            return false;
        }

    private:
        point3 center;
        double radius;
};

#endif
