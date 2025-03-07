#ifndef HITTABLE_H
#define HITTABLE_H

#include "hit_record.h"

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval& i, hit_record& rec) const = 0;
        std::string name; // for debug
};

#endif
