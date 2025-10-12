#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H

#include "ray.h"
#include "light.h"

class area_light {
    public:
        point3 position;
        color3 intensity;
        vec u;
        vec v;

        area_light(const point3& position, const color3& intensity, const vec& u, const vec& v)
            : position(position)
            , intensity(intensity)
            , u(u)
            , v(v) {}

        std::vector<light> sample(int n = 8) {
            std::vector<light> sample = {};

            for (int i = 0; i < 8; i += 1) {
                light light(
                    position
                        + random_double(0.0, 1.0) * u
                        + random_double(0.0, 1.0) * v,
                    intensity
                );

                sample.push_back(light);
            }

            return sample;
        }
};


#endif
