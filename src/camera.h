#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>

#include "ray.h"
#include "scene.h"
#include "logger.h"

inline double degrees_to_radians(double degrees) {
    static const double pi = 3.141592653589793;
    return degrees * pi / 180.0;
}

struct camera_opts {
    std::string mode;
    double      aspect_ratio;
    int         image_width;
    int         samples_per_pixel;
    int         max_depth;
    double      vfov;
    point3      lookfrom;
    point3      lookat;
    vec3        vup;
};

class camera {
    public:
        std::string mode                = MODE_FULL;
        double      aspect_ratio        = 1.0;
        int         image_width         = 100;
        int         samples_per_pixel   = 10;
        int         max_depth           = 10;
        double      vfov                = 90;
        point3      lookfrom            = point3(0, 0, 0);      // Point camera is looking from
        point3      lookat              = point3(0, 0, -1);     // Point camera is looking at
        vec3        vup                 = vec3(0, 1, 0);        // Camera "up" direction

        double      defocus_angle       = 0;
        double      focus_dist          = 10;

        void initialize(const camera_opts& opts) {
            mode                = opts.mode;
            aspect_ratio        = opts.aspect_ratio;
            image_width         = opts.image_width;
            samples_per_pixel   = opts.samples_per_pixel;
            max_depth           = opts.max_depth;
            vfov                = opts.vfov;
            lookfrom            = opts.lookfrom;
            lookat              = opts.lookat;
            vup                 = opts.vup;

            setup();
        }

        color3matrix render(scene& scene) {
            color3matrix matrix;

            logger logger(image_width * image_height);
            logger.start();

            for (int j = 0; j < image_height; j += 1) {
                std::vector<color3> row;

                for (int i = 0; i < image_width; i += 1) {
                    color3 pixel = color3(0.0, 0.0, 0.0);

                    for (int s = 0; s < samples_per_pixel; s += 1) {
                        pixel += scene.illuminance_v2(get_ray(i, j), max_depth);
                        // pixel += scene.illuminance_v1(get_ray(i, j), mode, max_depth);
                    }

                    row.push_back(pixel * pixel_samples_scale);
                    logger.tick();
                }

                matrix.push_back(row);
            }

            logger.end();

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

        void setup() {
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

        ray get_ray(int i, int j) {
            vec3 randon_offset = 0.5 * random_in_unit_square();

            vec3 direction = pixel00_loc
                + (i + randon_offset.x()) * pixel_delta_u
                + (j + randon_offset.y()) * pixel_delta_v
                - center;

            return ray(center, direction);
        }
};

#endif
