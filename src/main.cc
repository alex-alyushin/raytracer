#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "camera.h"
#include "image.h"
#include "params.h"
#include "parser.h"
#include "print_object_stats.h"

std::pair<std::string, std::string> key_value(const std::string& token) {
    auto pos = token.find('=');

    if (pos != std::string::npos) {
        return { token.substr(0, pos), token.substr(pos + 1) };
    }

    return {};
}

int main(int argc, char* argv[]) {
    std::cout << "[RayTracer v2.0.0] running..." << std::endl;

    std::string config = "";

    for (int index = 0; index < argc; index += 1) {
        auto [ key, val ] = key_value(argv[index]);

        if (key == "--cfg") {
            config = val;
        }
    }

    auto [ input_file, output_file, camera_opts ] = params::read(config);

    scene scene; // on the stack

    parser::read_objects(scene, input_file);

    camera camera;
    camera.initialize(camera_opts);
    auto matrix = camera.render(scene);

    image image{matrix};
    image.post_processing();
    image.store(output_file);

    // @debug
    print_object_statistics();

    return 0;
}
