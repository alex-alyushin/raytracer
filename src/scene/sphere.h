#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class sphere {
    public:
        sphere(const point3& center, double radius, material& mtl)
            : center(center)
            , radius(radius)
            , mat(mtl) {}

        std::optional<intersection> hit(const ray& ray, const interval& interval) const {
            auto OC = center - ray.origin();
            auto H = dot(ray.direction(), OC);

            auto a = ray.direction().length_squared();
            auto c = OC.length_squared() - radius * radius;

            auto discriminant = H * H - a * c;

            if (discriminant < 0) {
                return std::nullopt;
            }

            auto sqrtd = std::sqrt(discriminant);
            auto root = (H - sqrtd) / a;

            if (!interval.surrounds(root)) {
                root = (H + sqrtd) / a;

                if (!interval.surrounds(root)) {
                    return std::nullopt;
                }
            }

            intersection rec(
                mat,
                ray.at(root),
                root
            );

            vec outward_normal = (rec.point - center) / radius;
            rec.set_front_face(ray, outward_normal);
            rec.set_normal(outward_normal);

            return rec;
        }

    private:
        point3 center;
        double radius;
        material& mat;
};

#endif
