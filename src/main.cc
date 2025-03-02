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
#include "hittable_vector.h"
#include "sphere.h"
#include "camera.h"

#include "examples/stab.h"
#include "examples/scene_1.h"

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v1.3.0] running..." << std::endl;

    std::string mode;

    for (int index = 0; index < argc; ++index) {
        auto pair = parse_arguments(argv[index]);
        auto key = pair.first;
        auto value = pair.second;

        if (key == "mode") {
            mode = value;
        }
    }

    auto scene = getScene();
    auto matrix = renderScene(scene);
    auto output = "src/artefacts/scene.png";

    create_png(matrix, output);

    return 0;
}
