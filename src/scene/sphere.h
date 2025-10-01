#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class sphere : public object {
    public:
        sphere(const point3& center, double radius, std::shared_ptr<material> model)
            : center(center)
            , radius(radius)
            , mat(model) {}

        std::optional<intersection> hit(const ray& ray, const interval& interval) const override {
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

            intersection rec;

            rec.t       = root;
            rec.point   = ray.at(rec.t);
            rec.mat     = mat;

            vec outward_normal = (rec.point - center) / radius;

            rec.set_front_face(ray, outward_normal);
            rec.set_normal(outward_normal);

            return rec;
        }

    private:
        point3 center;
        double radius;
        std::shared_ptr<material> mat;
};

#endif
