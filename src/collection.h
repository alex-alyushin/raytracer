#ifndef HITTABLE_VECTOR_H
#define HITTABLE_VECTOR_H

#include <vector>
#include <memory>
#include <optional>

#include "hittable.h"

class collection : public hittable {
    public:
        std::vector<std::shared_ptr<hittable>> objects;

        collection() {}

        collection(std::shared_ptr<hittable> object) {
            add(object);
        }

        void add(std::shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        void clear() {
            objects.clear();
        }

        bool hit(const ray& r, interval& i, hit_record& rec) const override {
            bool hit_anything = false;

            hit_record closest_rec;
            closest_rec.t = -1;

            for (const auto& object : objects) {
                if (object->hit(r, i, rec)) {
                    hit_anything = true;

                    if (closest_rec.t < 0 || closest_rec.t > rec.t) {
                        closest_rec = rec;
                    }
                }
            }

            rec = closest_rec;

            return hit_anything;
        }
};

#endif
