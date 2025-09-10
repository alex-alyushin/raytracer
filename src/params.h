#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include <string>
#include <iostream>

struct params_t {
    std::string mode;
    std::string obj_file;
    std::string opt_file;
    std::string output;
};

const params_t DEFAULT_PARAMS = {
    "full",
    "scenes/cube.obj",
    "scenes/cube.opt",
    "scenes/cube.png",
};

std::pair<std::string, std::string> key_value(const std::string& arg) {
    auto pos = arg.find('=');

    if (pos != std::string::npos) {
        return { arg.substr(0, pos), arg.substr(pos + 1)};
    }

    return {};
}

params_t parse_params(int argc, char* argv[]) {
    params_t default_params = DEFAULT_PARAMS;

    for (int index = 0; index < argc; index += 1) {
        auto [ key, value ] = key_value(argv[index]);

        if (key == "--mode") {
            default_params.mode = value;
        }

        if (key == "--obj") {
            default_params.obj_file = value;
        }

        if (key == "--opt") {
            default_params.opt_file = value;
        }

        if (key == "--output") {
            default_params.output = value;
        }
    }

    return default_params;
}

#endif
