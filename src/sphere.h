#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, std::shared_ptr<material> mat, std::string n)
            : center(center)
            , radius(radius)
            , mat(mat) {
                name = n; // for debug
            }

        bool hit(const ray& r, interval& i, hit_record& rec) const override {
            auto OC = center - r.origin();
            auto H = dot(r.direction(), OC);

            auto a = r.direction().length_squared();
            auto c = OC.length_squared() - radius*radius;

            auto discriminant = H * H - a * c;

            if (discriminant < 0) {
                return false;
            }

            auto sqrtd = std::sqrt(discriminant);
            auto root = (H - sqrtd) / a;

            if (!i.surrounds(root)) {
                root = (H + sqrtd) / a;
            if (!i.surrounds(root))
                return false;
            }

            rec.t = root;
            rec.point = r.at(rec.t);
            rec.mat = mat;

            vec3 outward_normal = (rec.point - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }

        std::string name; // for debug

    private:
        point3 center;
        double radius;
        std::shared_ptr<material> mat;
};

#endif
