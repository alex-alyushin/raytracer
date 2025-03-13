#ifndef HIT_RECORD_H
#define HIT_RECORD_H

class material;
class hittable;

class hit_record {
    public:
        point3 point;
        vec3 normal;
        double t;
        std::shared_ptr<material> mat;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

#endif
