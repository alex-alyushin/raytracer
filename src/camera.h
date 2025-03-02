#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
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

        color3matrix render(std::shared_ptr<hittable> scene) {
            initialize();

            color3matrix matrix;

            int pixel_counter = 0;
            int rate1 = rate(pixel_counter, image_height, image_width);
            const auto start = std::chrono::high_resolution_clock::now();

            /* Main Render Cicle */
            for (int j = 0; j < image_height; j += 1) {
                std::vector<color3> row;

                for (int i = 0; i < image_width; i += 1) {
                    color3 pixel = BLACK;

                    for (int s = 0; s < samples_per_pixel; s += 1) {
                        auto r = getRay(i, j);
                        pixel += getColor(r, scene);
                    }

                    pixel_counter += 1;
                    int rate2 = rate(pixel_counter, image_height, image_width);
                    if (rate2 != rate1) {
                        std::cout
                            << "\rPixels rendered = "
                            << rate2 << "%"
                            << "\tTime = "
                            << banchmark(start)
                            << std::flush;

                        rate1 = rate2;
                    }

                    row.push_back(pixel_samples_scale * pixel);
                }

                matrix.push_back(row);
            }

            std::cout
                << std::endl
                << "Render completed in "
                << banchmark(start)
                << std::endl;

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

        vec3 sample_square() {
            return vec3(
                random_double() - 0.5,
                random_double() - 0.5,
                0
            );
        }

        ray getRay(int i, int j) {
            vec3 randon_offset = sample_square();
            vec3 direction = pixel00_loc
                + (i + randon_offset.x()) * pixel_delta_u
                + (j + randon_offset.y()) * pixel_delta_v
                - center;

            return ray(center, direction);
        }

        color3 getColor(const ray& ray, std::shared_ptr<hittable> scene) {
            hit_record rec;

            if (scene->hit(ray, rec)) {
                const double min = 3.0;
                const double max = 9.9;
                auto channel = 255 * (max - rec.t) / (max - min);

                return color3(channel, channel, channel);
            }

            return WHITE;
        }
};

#endif
