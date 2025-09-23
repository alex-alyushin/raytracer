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
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif
