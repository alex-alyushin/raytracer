#ifndef HIT_RECORD_H
#define HIT_RECORD_H

class hit_record {
    public:
        point3 point;
        vec3 normal;
        double t;

        hit_record& operator=(const hit_record& other) {
            if (this != &other) {
                this->point = other.point;
                this->normal = other.normal;
                this->t = other.t;
            }

            return *this;
        }
};

#endif
