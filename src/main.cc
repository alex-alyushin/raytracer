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
#include "options.h"

#include "examples/scene_1.h"
#include "examples/scene_2.h"
#include "examples/scene_3.h"
#include "examples/scene_4.h"

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v1.8.0] running..." << std::endl;

    auto options = parse_options(argc, argv);

    auto matrix = renderScene2(getScene2(), options.mode);
    create_png(matrix, options.output);

    return 0;
}
