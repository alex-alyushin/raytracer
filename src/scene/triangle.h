#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class triangle : public object {
    public:
        triangle(
            std::shared_ptr<material> mat,
            std::shared_ptr<point3> vertex_0,
            std::shared_ptr<point3> vertex_1,
            std::shared_ptr<point3> vertex_2,
            std::shared_ptr<vec> normal_0,
            std::shared_ptr<vec> normal_1,
            std::shared_ptr<vec> normal_2
        )
            : mat(mat)
            , vertex_0(vertex_0)
            , vertex_1(vertex_1)
            , vertex_2(vertex_2)
            , normal_0(normal_0)
            , normal_1(normal_1)
            , normal_2(normal_2) {}

        vec normal_component(int8_t index) const {
            if (index == 0 && normal_0 != nullptr) {
                return *normal_0;
            }

            if (index == 1 && normal_1 != nullptr) {
                return *normal_1;
            }

            if (index == 2 && normal_2 != nullptr) {
                return *normal_2;
            }

            return vec{0, 0, 0};
        }

        vec normal(const point3& point) const {
            auto triangle_area = [](const point3& v0, const point3& v1, const point3& v2) {
                return cross(v1 - v0, v2 - v0).length() / 2;
            };

            const double s = triangle_area(*vertex_0, *vertex_1, *vertex_2);
            const double u = triangle_area(point, *vertex_1, *vertex_2) / s;
            const double v = triangle_area(point, *vertex_2, *vertex_0) / s;
            const double w = triangle_area(point, *vertex_0, *vertex_1) / s;

            return unit_vector(
                normal_component(0) * u +
                normal_component(1) * v +
                normal_component(2) * w
            );
        }

        std::optional<intersection> hit(const ray& ray, const interval& interval) const override {
            constexpr double epsilon = std::numeric_limits<double>::epsilon();

            vec edge_1 = *vertex_1 - *vertex_0;
            vec edge_2 = *vertex_2 - *vertex_0;

            vec ray_cross_edge_2 = cross(ray.direction(), edge_2);
            double det = dot(edge_1, ray_cross_edge_2);

            if (det > -epsilon && det < epsilon) {
                return std::nullopt;
            }

            vec s = ray.origin() - *vertex_0;
            double u = (1.0 / det) * dot(s, ray_cross_edge_2);

            if ((u < 0 && std::abs(u) > epsilon) || (u > 1 && std::abs(u - 1) > epsilon)) {
                return std::nullopt;
            }

            vec s_cross_edge_1 = cross(s, edge_1);
            double v = (1.0 / det) * dot(ray.direction(), s_cross_edge_1);

            if ((v < 0 && std::abs(v) > epsilon) || (u + v > 1 && std::abs(u + v - 1) > epsilon)) {
                return std::nullopt;
            }

            double t = (1.0 / det) * dot(edge_2, s_cross_edge_1);

            if (t < epsilon) {
                return std::nullopt;
            }

            intersection rec;
            rec.t       = t;
            rec.point   = ray.at(rec.t);
            rec.mat     = mat;
            // rec.set_front_face(ray, n);
            rec.set_normal(normal(rec.point));

            return rec;
        }

    private:
        std::shared_ptr<material> mat;

        std::shared_ptr<point3> vertex_0;
        std::shared_ptr<point3> vertex_1;
        std::shared_ptr<point3> vertex_2;

        std::shared_ptr<vec> normal_0;
        std::shared_ptr<vec> normal_1;
        std::shared_ptr<vec> normal_2;
};

#endif
