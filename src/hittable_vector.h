#ifndef HITTABLE_VECTOR_H
#define HITTABLE_VECTOR_H

#include <vector>
#include <memory>

#include "hittable.h"

class hittable_vector : public hittable {
    public:
        std::vector<std::shared_ptr<hittable>> objects;

        hittable_vector() {}

        hittable_vector(std::shared_ptr<hittable> object) {
            add(object);
        }

        void add(std::shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        void clear() {
            objects.clear();
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            bool hit_anything = false;

            for (const auto& object : objects) {
                if (object->hit(r, interval(0.0, 100.0), rec)) {
                    hit_anything = true;
                }
            }

            return hit_anything;
        }
};

#endif
