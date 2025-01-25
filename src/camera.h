#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera {
    public:
        double  aspect_ratio        = 1.0;
        int     image_width         = 100;
        int     samples_per_pixel   = 10;
        int     max_depth           = 10;

        double  vfov                = 90;

        point3  lookfrom            = point3(0, 0, 0);  // Point camera is looking from
        point3  lookat              = point3(0, 0, -1); // Point camera is looking at
        vec3    vup                 = vec3(0, 1, 0);    // Camera "up" direction

        double  defocus_angle       = 0;
        double  focus_dist          = 10;

        void render(const hittable& world) {
            initialize();

            // and many other...

            std::clog << "Rendering completed" << '\n';
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
            throw std::runtime_error("Unimplemented method");
        }
};

#endif
