#ifndef PARAMS_READER_H
#define PARAMS_READER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>

#include "camera.h"

class params_reader {
    public:
        static std::tuple<std::string, std::string, camera_opts> read(const std::string& filename);
};

std::tuple<std::string, std::string, camera_opts> params_reader::read(const std::string& filename) {
    std::string input_file;
    std::string output_file;
    camera_opts camera_opts;

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

        if (key == "input_file") {
            input_file = val;
        }

        if (key == "output_file") {
            output_file = val;
        }

        if (key == "mode") {
            camera_opts.mode = val;
        }

        if (key == "aspect_ratio") {
            camera_opts.aspect_ratio = std::stod(val);
        }

        if (key == "image_width") {
            camera_opts.image_width = std::stoi(val);
        }

        if (key == "samples_per_pixel") {
            camera_opts.samples_per_pixel = std::stoi(val);
        }

        if (key == "max_depth") {
            camera_opts.max_depth = std::stoi(val);
        }

        if (key == "vfov") {
            camera_opts.vfov = std::stod(val);
        }

        if (key == "lookfrom" || key == "lookat" || key == "vup") {
            std::stringstream ss(val);

            double x, y, z;
            char comma;

            ss
                >> x >> comma
                >> y >> comma
                >> z;

            if (key == "lookfrom") {
                camera_opts.lookfrom = point3(x, y, z);
            }

            if (key == "lookat") {
                camera_opts.lookat = point3(x, y, z);
            }

            if (key == "vup") {
                camera_opts.vup = vec3(x, y, z);
            }
        }
    }

    return { input_file, output_file, camera_opts };
}

#endif
