#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include <string>
#include <iostream>

struct render_opts {
    std::string mode;
    std::string obj_file;
    std::string mtl_file;
    std::string output;
};

std::pair<std::string, std::string> parse_arguments(const std::string& arg) {
    auto pos = arg.find('=');

    if (pos != std::string::npos) {
        return { arg.substr(0, pos), arg.substr(pos + 1)};
    }

    return {};
}

render_opts parse_options(int argc, char* argv[]) {

    render_opts options = {
        "full",
        "scenes/cube.obj",
        "scenes/cube.mtl",
        "renders/out.png",
    };

    for (int index = 0; index < argc; index += 1) {
        auto [ key, value ] = parse_arguments(argv[index]);

        if (key == "--mode") {
            options.mode = value;
        }

        if (key == "--obj") {
            options.obj_file = value;
        }

        if (key == "--mtl") {
            options.mtl_file = value;
        }

        if (key == "--output") {
            options.output = value;
        }
    }

    return options;
}

#endif
