#ifndef HIT_RECORD_H
#define HIT_RECORD_H

class material_model;
class hittable;

struct hit_record {
    point3 point;
    vec3 normal;
    double t;
    std::shared_ptr<material_model> mat;

    bool front_face;
    inline void set_face_normal(const ray& ray, const vec3& outward_normal) {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

    inline ray specular_reflected(const ray& ray_in);
    inline ray diffuse_reflected();
};

inline ray hit_record::specular_reflected(const ray& ray_in) {
    auto direction = ray_in.direction();

    return ray(
        point,
        unit_vector(direction - 2 * dot(direction, normal) * normal)
    );
}

inline ray hit_record::diffuse_reflected() {
    return ray(
        point,
        unit_vector(normal) + random_unit_vector()
    );
}

// inline vec3 refraction(const vec3& direction, const hit_record& rec, double refraction_index) {
//     double etai = rec.front_face ? (1 / refraction_index) : refraction_index;

//     auto unit_direct = unit_vector(direction);
//     auto unit_normal = unit_vector(rec.normal);

//     auto cos = std::fmin(dot(-unit_direct, unit_normal), 1.0);
//     auto ray_out_norm = etai * (unit_direct + cos * unit_normal);
//     auto ray_out_tang = -1 * std::sqrt(std::fabs(1.0 - ray_out_norm.length_squared())) * rec.normal;

//     return ray_out_norm + ray_out_tang;
// }

#endif
