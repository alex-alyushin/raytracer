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

using high_resolution_time = std::chrono::time_point<std::chrono::high_resolution_clock>;

const auto BLACK = color3(0.0, 0.0, 0.0);
const auto WHITE = color3(1.0, 1.0, 1.0);

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

        color3matrix render(std::shared_ptr<collection> scene) {
            initialize();
            color3matrix matrix;

            /* Log Info */
            const auto start = std::chrono::high_resolution_clock::now();
            int progress_in_pixels = 0;
            int progress_in_percentage = int(
                100 * progress_in_pixels
                / (image_height * image_width)
            );

            /* Main Render Cicle */
            for (int j = 0; j < image_height; j += 1) {
                std::vector<color3> row;

                for (int i = 0; i < image_width; i += 1) {
                    color3 pixel = BLACK;

                    for (int s = 0; s < samples_per_pixel; s += 1) {
                        auto camera_ray = getRay(i, j);
                        pixel += getColor(camera_ray, max_depth, scene);
                    }

                    row.push_back(write_pixel(pixel_samples_scale * pixel));
                    progress(start, progress_in_pixels, progress_in_percentage);
                }

                matrix.push_back(row);
            }

            completed(start);

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

        // [depth, freq]
        std::unordered_map<int, int> calls_cache;

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

        void progress(const high_resolution_time& start, int& progress_in_pixels, int& progress_in_percentage) {
            int progress_new = int(
                100 * (progress_in_pixels += 1)
                / (image_height * image_width)
            );

            if (progress_new != progress_in_percentage) {
                std::cout
                    << "\rPixels rendered = "
                    << progress_new << "%"
                    << "\tTime = "
                    << benchmark(start)
                    << std::flush;

                progress_in_percentage = progress_new;
            }
        }

        void completed(const high_resolution_time& start) {
            std::cout << "\nDepth stats:" << std::endl;

            for (auto& p : calls_cache) {
                std::cout << "d = " << p.first << "\tcount = " << p.second << std::endl;
            }

            std::cout
                << "[C++] Render completed in time "
                << benchmark(start)
                << std::endl;
        }

        std::string benchmark(const high_resolution_time& start) {
            const auto end = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration % std::chrono::hours(1)).count();
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration % std::chrono::minutes(1)).count();

            return std::to_string(minutes) + ":"
                + (seconds < 10 ? "0" : "") + std::to_string(seconds);
        };

        void save_to_cache(int depth) {
            if (calls_cache.find(depth) != calls_cache.end()) {
                calls_cache[depth] += 1;
            } else {
                calls_cache[depth] = 1;
            }
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

        color3 getSky(const ray& camera_ray) {
            auto unit_direction = unit_vector(camera_ray.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);

            return (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);
        }

        color3 getColor(const ray& camera_ray, int depth, std::shared_ptr<collection> scene) {
            save_to_cache(depth);

            if (depth < 0) {
                return BLACK;
            }

            hit_record rec;
            interval hit_interval(0.001, std::numeric_limits<double>::infinity());

            if (scene->hit(camera_ray, hit_interval, rec)) {
                ray scattered;
                color3 attenuation;

                if (rec.mat->scatter(camera_ray, rec, attenuation, scattered)) {
                    return attenuation * getColor(scattered, depth - 1, scene);
                }

                return BLACK;
            }

            return getSky(camera_ray);
        }
};

#endif
