#ifndef PHYSICS_H
#define PHYSICS_H

#include "vec3.h"

inline vec3 specular_reflected_vec(const vec3& direction, const vec3& normal) {
    return unit_vector(direction - 2 * dot(direction, normal) * normal);
}

inline vec3 diffuse_reflected_vec(const vec3& normal) {
    return unit_vector(normal) + random_unit_vector();
}

inline vec3 refracted_vec(const vec3& v, const vec3& n, double etai) {
    auto cos = std::fmin(dot(-v, n), 1.0);
    auto ray_out_normal = etai * (v + cos * n);
    auto ray_out_tangent = -std::sqrt(std::fabs(1.0 - ray_out_normal.length_squared())) * n;

    return ray_out_normal + ray_out_tangent;
}

#endif
