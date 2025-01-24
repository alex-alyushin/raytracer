#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(radius) {}

        bool hit(/* const ray& r, double ray_tmin, double ray_tmax, hit_record& rec */) const override {
            // todo: calculate discriminant of intersection with ray
            throw std::runtime_error("Unimplemented method");

            return true;
        }

    private:
        point3 center;
        double radius;
};

#endif
