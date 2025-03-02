#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, std::shared_ptr<material> mat)
            : center(center)
            , radius(radius)
            , mat(mat) {}

        bool hit(const ray& r, hit_record& rec) const override {
            auto origin = r.origin();
            auto direction = r.direction();
            auto h = cross(center - origin, unit_vector(direction)).length();

            if (h <= radius) {
                rec.t = std::sqrt((center - origin).length_squared() - h * h)
                      - std::sqrt(radius * radius - h * h);
                rec.point = r.at(rec.t);
                rec.normal = unit_vector(rec.point - center);
                rec.mat = mat;

                return true;
            }

            return false;
        }

    private:
        point3 center;
        double radius;
        std::shared_ptr<material> mat;
};

#endif
