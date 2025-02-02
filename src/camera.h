#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <cmath>

#include "hittable.h"
#include "material.h"
#include "ray.h"

#include "utils.h"

const auto BLACK = color3(0, 0, 0);
const auto WHITE = color3(255, 255, 255);

class camera {
    public:
        double  aspect_ratio        = 1.0;
        int     image_width         = 100;
        int     samples_per_pixel   = 10;
        int     max_depth           = 10;

        double  vfov                = 90;

        point3  lookfrom            = point3(0, 0, 0);      // Point camera is looking from
        point3  lookat              = point3(0, 0, -1);     // Point camera is looking at
        vec3    vup                 = vec3(0, 1, 0);        // Camera "up" direction

        double  defocus_angle       = 0;
        double  focus_dist          = 10;

        color3matrix render(std::shared_ptr<hittable> scene, const std::string& mode) {
            std::cout << "[render]" << std::endl;

            initialize();

            color3matrix matrix;

            int counter_all = 0;
            int counter_hit = 0;

            hit_record rec;
            interval rng(-1.0, -1.0);

            for (int j = 0; j < image_height; j += 1) {
                std::vector<color3> row;

                for (int i = 0; i < image_width; i += 1) {
                    if (scene->hit(getRay(i, j), rng, rec)) {
                        row.push_back(getColor(rec, rng, mode));

                        counter_hit += 1;
                    } else {
                        row.push_back(WHITE);
                    }

                    counter_all += 1;
                }

                matrix.push_back(row);
            }

            auto hitrate = 100 * double(counter_hit) / counter_all;
            std::cout << "Hit Rate = " << hitrate << "%" << std::endl;
            std::cout << "Counter all = " << counter_all << std::endl;
            std::cout << "Counter hit = " << counter_hit << std::endl;

            return matrix;
        }

    private:
        int     image_height;
        double  pixel_samples_scale;
        point3  center;
        point3  pixel00_loc;
        vec3    pixel_delta_u;
        vec3    pixel_delta_v;
        vec3    u, v, w;
        vec3    defocus_disk_u;
        vec3    defocus_disk_v;

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            center = lookfrom;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            auto theta = degrees_to_radians(vfov);
            auto H = std::tan(theta / 2);

            auto viewport_height = 2 * H * focus_dist;
            auto viewport_width = viewport_height * (double(image_width) / image_height);

            vec3 viewport_u = viewport_width * u;
            vec3 viewport_v = viewport_height * -v;

            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }

        ray getRay(int i, int j) {
            vec3 direction = (
                pixel00_loc
                    + i * pixel_delta_u
                    + j * pixel_delta_v
                    - center
            );

            return ray(center, direction);
        }

        color3 getColor(const hit_record& rec, interval& rng, const std::string& mode) {
            if (mode == "simple") {
                return BLACK;
            }

            if (mode == "in-depth") {
                const double min = 3.0;
                const double max = 9.9;
                auto channel = 255 * (max - rec.t) / (max - min);

                return color3(channel, channel, channel);
            }

            if (mode == "normales") {
                return color3(
                    255 * (rec.normal.x() + 1) / 2,
                    255 * (rec.normal.y() + 1) / 2,
                    255 * (rec.normal.z() + 1) / 2
                );
            }

            return WHITE;
        }
};

#endif
