#ifndef HIT_RECORD_H
#define HIT_RECORD_H

class material;

class hit_record {
    public:
        point3 point;
        vec3 normal;
        double t;
        std::shared_ptr<material> mat;
};

#endif
