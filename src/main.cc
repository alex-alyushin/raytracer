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

#include "examples/stab.h"
#include "examples/scene_1.h"

std::pair<std::string, std::string> parse_arguments(const std::string& arg) {
    size_t pos = arg.find('=');

    if (pos != std::string::npos) {
        std::string key = arg.substr(0, pos);
        std::string value = arg.substr(pos + 1);

        return std::pair<std::string, std::string>(key, value);
    }

    return std::pair<std::string, std::string>();
}

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v1.4.0] running..." << std::endl;

    std::string mode;
    std::string output = "out.png";

    for (int index = 0; index < argc; ++index) {
        auto pair = parse_arguments(argv[index]);
        auto key = pair.first;
        auto value = pair.second;

        if (key == "--mode" || key == "-m") {
            mode = value;
        }

        if (key == "--output" || key == "-o") {
            output = value;
        }
    }

    auto matrix = renderScene(getScene());
    create_png(matrix, "src/artefacts/" + output);

    return 0;
}
