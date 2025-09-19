#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>

#include "ray.h"
#include "collection.h"
#include "logger.h"

// @todo: [scene] move it to scene
// used just for method get_color
#include "material.h"
#include "hit_record.h"
#include "interval.h"

const auto BLACK = color3(0.0, 0.0, 0.0);
const auto WHITE = color3(1.0, 1.0, 1.0);

const auto MODE_DEPT = "dept";
const auto MODE_NORM = "norm";
const auto MODE_FULL = "full";

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

        color3matrix render(std::shared_ptr<collection> scene) {
            color3matrix matrix;

            logger logger(image_width * image_height);
            logger.start();

            for (int j = 0; j < image_height; j += 1) {
                std::vector<color3> row;

                for (int i = 0; i < image_width; i += 1) {
                    color3 pixel = BLACK;

                    for (int s = 0; s < samples_per_pixel; s += 1) {
                        // @todo: [scene] intensity must be calculated in class scene
                        pixel += get_color(get_ray(i, j), scene, mode, max_depth);
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

        vec3 sample_square() {
            return 0.5 * random_in_unit_square();
        }

        ray get_ray(int i, int j) {
            vec3 randon_offset = sample_square();

            vec3 direction = pixel00_loc
                + (i + randon_offset.x()) * pixel_delta_u
                + (j + randon_offset.y()) * pixel_delta_v
                - center;

            return ray(center, direction);
        }

        color3 get_sky(const ray& camera_ray) {
            auto unit_direction = unit_vector(camera_ray.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);

            return (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);
        }

        color3 get_color(const ray& camera_ray, std::shared_ptr<collection> scene, std::string mode, int depth) {
            if (depth < 0) {
                return get_sky(camera_ray);
            }

            hit_record rec;
            interval interval(0.001);

            if (scene->hit(camera_ray, interval, rec)) {

                if (mode == MODE_DEPT) {
                    double gray = std::exp(-rec.t);
                    return color3(gray, gray, gray);
                }

                if (mode == MODE_NORM) {
                    double R = (rec.normal.x() + 1.0) / 2;
                    double G = (rec.normal.y() + 1.0) / 2;
                    double B = (rec.normal.z() + 1.0) / 2;

                    return color3(R, G, B);
                }

                if (mode == MODE_FULL) {
                    ray scattered;
                    color3 attenuation;

                    if (rec.mat->scatter(camera_ray, rec, attenuation, scattered)) {
                        return attenuation * get_color(scattered, scene, mode, depth - 1);
                    }

                    return BLACK;
                }

                std::cerr << "[Render] unknown render mode: " << mode << std::endl;
                exit(1);
            }

            return get_sky(camera_ray);
        }
};

#endif
