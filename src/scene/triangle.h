#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class triangle {
    public:
        triangle(
            point3& vertex_0,
            point3& vertex_1,
            point3& vertex_2,
            vec& normal_0,
            vec& normal_1,
            vec& normal_2,
            material& mtl
        )
            : vertex_0(vertex_0)
            , vertex_1(vertex_1)
            , vertex_2(vertex_2)
            , normal_0(normal_0)
            , normal_1(normal_1)
            , normal_2(normal_2)
            , mat(mtl) {}

        vec normal(const point3& point) const {
            auto triangle_area = [](const point3& v0, const point3& v1, const point3& v2) {
                return cross(v1 - v0, v2 - v0).length() / 2;
            };

            const double s = triangle_area(vertex_0, vertex_1, vertex_2);
            const double u = triangle_area(point, vertex_1, vertex_2) / s;
            const double v = triangle_area(point, vertex_2, vertex_0) / s;
            const double w = triangle_area(point, vertex_0, vertex_1) / s;

            return unit_vector(
                normal_0 * u +
                normal_1 * v +
                normal_2 * w
            );
        }

        std::optional<intersection> hit(const ray& ray, const interval& interval) const {
            constexpr double epsilon = std::numeric_limits<double>::epsilon();

            vec edge_1 = vertex_1 - vertex_0;
            vec edge_2 = vertex_2 - vertex_0;

            vec ray_cross_edge_2 = cross(ray.direction(), edge_2);
            double det = dot(edge_1, ray_cross_edge_2);

            if (det > -epsilon && det < epsilon) {
                return std::nullopt;
            }

            vec s = ray.origin() - vertex_0;
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

            intersection rec(
                mat,
                ray.at(t),
                t
            );

            // rec.set_front_face(ray, n);
            rec.set_normal(normal(rec.point));

            return rec;
        }

    private:
        point3& vertex_0;
        point3& vertex_1;
        point3& vertex_2;

        vec& normal_0;
        vec& normal_1;
        vec& normal_2;

        material& mat;
};

#endif
