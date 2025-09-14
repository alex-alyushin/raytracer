#include <vector>
#include <string>
#include <iostream>

#include "png.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "hit_record.h"
#include "material.h"
#include "hittable.h"
#include "collection.h"
#include "sphere.h"
#include "camera.h"
#include "params.h"
#include "reader.h"

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v1.9.0] running..." << std::endl;
    auto [ mode, obj_file, opt_file, output ] = parse_params(argc, argv);

    camera cam;

    auto opts = reader::read_camera_opts(opt_file);
    cam.initialize(opts);

    auto scene = reader::read_objects(obj_file);
    auto matrix = cam.render(scene, mode);

    create_png(matrix, output);

    return 0;
}
