#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class sphere {
    public:
        sphere(const point3& center, double radius, material* mtl)
            : center(center)
            , radius(radius)
            , mat(mtl) {}

        bool hit(const ray& ray, const interval& interval, intersection& intersection) const {
            auto OC = center - ray.origin();
            auto H = dot(ray.direction(), OC);

            auto a = ray.direction().length_squared();
            auto c = OC.length_squared() - radius * radius;

            auto discriminant = H * H - a * c;

            if (discriminant < 0) {
                return false;
            }

            auto sqrtd = std::sqrt(discriminant);
            auto root = (H - sqrtd) / a;

            if (!interval.surrounds(root)) {
                root = (H + sqrtd) / a;

                if (!interval.surrounds(root)) {
                    return false;
                }
            }

            intersection.mat = mat;
            intersection.point = ray.at(root);
            intersection.t = root;

            vec outward_normal = (intersection.point - center) / radius;
            intersection.set_front_face(ray, outward_normal);
            intersection.set_normal(outward_normal);
 
            return true;
        }

    private:
        point3 center;
        double radius;
        material* mat;
};

#endif
