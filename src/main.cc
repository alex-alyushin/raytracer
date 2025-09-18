#include <vector>
#include <string>
#include <iostream>

#include "image.h"
#include "ray.h"
#include "vec3.h"
#include "hit_record.h"
#include "material.h"
#include "hittable.h"
#include "collection.h"
#include "sphere.h"
#include "camera.h"
#include "params.h"
#include "file_reader.h"

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v1.9.1] running..." << std::endl;

    std::string cfg = "";

    for (int index = 0; index < argc; index += 1) {
        auto [ key, val ] = params::key_value(argv[index]);

        if (key == "--cfg") {
            cfg = val;
        }
    }

    auto [ camera_opts, render_opts ] = params::parse_cfg(cfg);

    camera camera;
    camera.initialize(camera_opts);

    std::shared_ptr<collection> scene = file_reader::read_scene(render_opts.obj_file);
    color3matrix matrix = camera.render(scene, render_opts.mode);
    image::write_to_png(matrix, render_opts.output);

    return 0;
}
