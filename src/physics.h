#ifndef PHYSICS_H
#define PHYSICS_H

#include "vec3.h"
#include "hit_record.h"
#include "random.h"

inline vec3 mirror_reflection(const vec3& direction, const hit_record& rec) {
    return unit_vector(direction - 2 * dot(direction, rec.normal) * rec.normal);
}

inline vec3 diffuse_reflection(const hit_record& rec) {
    return unit_vector(rec.normal) + random_unit_vector();
}

inline vec3 refraction(const vec3& direction, const hit_record& rec, double refraction_index) {
    double etai = rec.front_face ? (1 / refraction_index) : refraction_index;

    auto unit_direct = unit_vector(direction);
    auto unit_normal = unit_vector(rec.normal);

    auto cos = std::fmin(dot(-unit_direct, unit_normal), 1.0);
    auto ray_out_norm = etai * (unit_direct + cos * unit_normal);
    auto ray_out_tang = -1 * std::sqrt(std::fabs(1.0 - ray_out_norm.length_squared())) * rec.normal;

    return ray_out_norm + ray_out_tang;
}

#endif
