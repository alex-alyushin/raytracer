#ifndef INTERSECTION_H
#define INTERSECTION_H

class material;
class object;

struct intersection {
    point3 point;
    vec normal;
    double t;
    std::shared_ptr<material> mat;

    bool front_face;
    inline void set_front_face(const ray& ray, const vec& outward_normal);
    inline void set_normal(const vec& outward_normal);

    inline ray get_specular_reflected(const ray& ray_in);
    inline ray get_diffuse_reflected();
};

inline void intersection::set_front_face(const ray& ray, const vec& outward_normal) {
    front_face = dot(ray.direction(), outward_normal) < 0;
}

inline void intersection::set_normal(const vec& outward_normal) {
    normal = front_face ? outward_normal : -outward_normal;
}

inline ray intersection::get_specular_reflected(const ray& ray_in) {
    auto reflected = ray_in.direction()
        - 2 * dot(ray_in.direction(), normal) * normal;

    return ray(point, unit_vector(reflected));
}

inline ray intersection::get_diffuse_reflected() {
    auto reflected = unit_vector(normal) + random_unit_vector();

    return ray(point, unit_vector(reflected));
}

// inline vec refraction(const vec& direction, const intersection& rec, double refraction_index) {
//     double etai = rec.front_face ? (1 / refraction_index) : refraction_index;

//     auto unit_direct = unit_vector(direction);
//     auto unit_normal = unit_vector(rec.normal);

//     auto cos = std::fmin(dot(-unit_direct, unit_normal), 1.0);
//     auto ray_out_norm = etai * (unit_direct + cos * unit_normal);
//     auto ray_out_tang = -1 * std::sqrt(std::fabs(1.0 - ray_out_norm.length_squared())) * rec.normal;

//     return ray_out_norm + ray_out_tang;
// }

#endif
