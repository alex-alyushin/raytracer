#include <iostream>
#include <string>
#include <vector>

#include "png.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "hit_record.h"
#include "material.h"
#include "hittable.h"
#include "hittable_vector.h"
#include "sphere.h"
#include "camera.h"

#include "examples/stab.h"
#include "examples/scene_1.h"

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v1.2.0] running..." << std::endl;

    std::string mode;

    for (int index = 0; index < argc; ++index) {
        auto pair = parse_arguments(argv[index]);
        auto key = pair.first;
        auto value = pair.second;

        if (key == "mode") {
            mode = value;
        }
    }

    if (mode == "stab") {
        std::cout << "[mode] stab" << std::endl;
        auto matrix = StabImage();
        create_png(matrix, "src/renders/[0]-stab.png");
    }

    if (mode == "simple") {
        std::cout << "[mode] simple" << std::endl;
        auto scene = getScene1();
        auto matrix = renderScene1(scene, mode);
        create_png(matrix, "src/renders/[1]-simple.png");
    }

    if (mode == "in-depth") {
        std::cout << "[mode] in-depth" << std::endl;
        auto scene = getScene1();
        auto matrix = renderScene1(scene, mode);
        create_png(matrix, "src/renders/[2]-in-depth.png");
    }

    if (mode == "normales") {
        std::cout << "[mode] normales" << std::endl;
        auto scene = getScene1();
        auto matrix = renderScene1(scene, mode);
        create_png(matrix, "src/renders/[3]-normales.png");
    }

    return 0;
}
