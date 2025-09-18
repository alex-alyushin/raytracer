#ifndef PARAMS_H
#define PARAMS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct render_opts {
    std::string obj_file;
    std::string output;
    std::string mode;
};

class params {
    public:
        static std::pair<std::string, std::string> key_value(const std::string& token);
        static std::pair<camera_opts, render_opts> parse_cfg(const std::string& filename);
};

std::pair<std::string, std::string> params::key_value(const std::string& token) {
    auto pos = token.find('=');

    if (pos != std::string::npos) {
        return { token.substr(0, pos), token.substr(pos + 1) };
    }

    return {};
}

std::pair<camera_opts, render_opts> params::parse_cfg(const std::string& filename) {
    camera_opts camera_opts;
    render_opts render_opts;

    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        auto pos = line.find('=');

        if (pos == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos + 1);


        /******************/
        /* Render Options */
        /******************/

        if (key == "obj_file") {
            render_opts.obj_file = val;
        }

        else if (key == "output") {
            render_opts.output = val;
        }

        else if (key == "mode") {
            render_opts.mode = val;
        }


        /******************/
        /* Camera Options */
        /******************/

        else if (key == "aspect_ratio") {
            camera_opts.aspect_ratio = std::stod(val);
        }

        else if (key == "image_width") {
            camera_opts.image_width = std::stoi(val);
        }

        else if (key == "samples_per_pixel") {
            camera_opts.samples_per_pixel = std::stoi(val);
        }

        else if (key == "max_depth") {
            camera_opts.max_depth = std::stoi(val);
        }

        else if (key == "vfov") {
            camera_opts.vfov = std::stod(val);
        }

        else if (key == "lookfrom" || key == "lookat" || key == "vup") {
            std::stringstream ss(val);

            double x, y, z;
            char comma;

            ss
                >> x
                >> comma
                >> y
                >> comma
                >> z;

            if (key == "lookfrom") {
                camera_opts.lookfrom = point3(x, y, z);
            }

            else if (key == "lookat") {
                camera_opts.lookat = point3(x, y, z);
            }

            else if (key == "vup") {
                camera_opts.vup = vec3(x, y, z);
            }
        }

        else {
            std::cerr << "[opt] unknown key" << std::endl;
        }
    }

    return { camera_opts, render_opts };
}

#endif
