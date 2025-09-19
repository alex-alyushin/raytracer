#include <vector>
#include <string>
#include <iostream>

#include "camera.h"
#include "image.h"
#include "opts_reader.h"
#include "scene_reader.h"

std::pair<std::string, std::string> key_value(const std::string& token) {
    auto pos = token.find('=');

    if (pos != std::string::npos) {
        return { token.substr(0, pos), token.substr(pos + 1) };
    }

    return {};
}

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v1.9.1] running..." << std::endl;

    std::string cfg = "";

    for (int index = 0; index < argc; index += 1) {
        auto [ key, val ] = key_value(argv[index]);

        if (key == "--cfg") {
            cfg = val;
        }
    }

    auto [ input_file, output_file, camera_opts ] = opts_reader::read(cfg);
    auto scene = scene_reader::read(input_file);

    camera camera;
    camera.initialize(camera_opts);
    auto matrix = camera.render(scene);

    image image{matrix};
    image.post_processing();
    image.store(output_file);

    return 0;
}
