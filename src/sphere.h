#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, std::shared_ptr<material> mat)
            : center(center)
            , radius(radius)
            , mat(mat) {}

        std::optional<hit_record> hit(const ray& ray, const interval& interval) const override {
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

            hit_record rec;
            rec.t       = root;
            rec.point   = ray.at(rec.t);
            rec.mat     = mat;

            vec3 outward_normal = (rec.point - center) / radius;
            rec.set_face_normal(ray, outward_normal);

            return rec;
        }

    private:
        point3 center;
        double radius;
        std::shared_ptr<material> mat;
};

#endif
