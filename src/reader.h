#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// @todo: implement mtl file parsing
auto material_stub = std::make_shared<metal>(color3(0.8, 0.6, 0.2), 0);


class reader {
    public:
        static std::shared_ptr<collection> read_objects(const std::string& filename);
        static camera_opts read_camera_opts(const std::string& filename);
    private:
        static void read_materials(const std::string& filename);
};

std::shared_ptr<collection> reader::read_objects(const std::string& filename) {
    std::cout << "[Reader] " << filename << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[Reader] cannot read objects" << std::endl;
        exit(1);
    }

    auto scene = std::make_shared<collection>();

    std::string line;

    while (std::getline(file, line)) {
        std::string word;
        std::vector<std::string> tokens;
        std::istringstream iss(line);

        while (iss >> word) {
            if (!word.empty()) {
                tokens.push_back(word);
            }
        }

        if (!tokens.empty()) {

            // Materials lib:   mtllib lib.mtl
            if (tokens[0] == "mtllib") {}

            // Use material:    usemtl mtl
            if (tokens[0] == "usemtl") {}

            // Sphere:          S x y z radius
            if (tokens[0] == "S") {
                if (tokens.size() != 5) {
                    std::cerr << "[Reader] sphere broken" << std::endl;
                }

                scene->add(std::make_shared<sphere>(
                    point3(
                        std::stod(tokens[1]),
                        std::stod(tokens[2]),
                        std::stod(tokens[3])
                    ),
                    std::stod(tokens[4]),
                    material_stub
                ));
            }

            // Vertex:          v
            if (tokens[0] == "v") {}

            // Vertex normale:  vn
            if (tokens[0] == "vn") {}

            // Vertex texture:  vt
            if (tokens[0] == "vt") {}

            // Face:            f
            if (tokens[0] == "f") {}

            // Lighter          P x y z R G B
            if (tokens[0] == "P") {}
        }
    }

    file.close();

    return scene;
}

void reader::read_materials(const std::string& filename) {
    std::cout << "[Reader] " << filename << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[Reader] cannot read materials" << std::endl;
        exit(1);
    }

    // @todo: implement mtl file parsing

    // newmtl name
    // Ka (ambient_color) it is the light from nowhere
    // Kd (diffuse_color)
    // Ks (specular_color)
    // Ke (intensity) as additive addition to ambient_color
    // Ns (specular_exponent)
    // Ni (refraction_index)
    // al (abledo)

    file.close();

    return;
}

camera_opts reader::read_camera_opts(const std::string& filename) {
    camera_opts opts;
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

        if (key == "aspect_ratio") {
            opts.aspect_ratio = std::stod(val);
        }

        else if (key == "image_width") {
            opts.image_width = std::stoi(val);
        }

        else if (key == "samples_per_pixel") {
            opts.samples_per_pixel = std::stoi(val);
        }

        else if (key == "max_depth") {
            opts.max_depth = std::stoi(val);
        }

        else if (key == "vfov") {
            opts.vfov = std::stod(val);
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
                opts.lookfrom = point3(x, y, z);
            }

            else if (key == "lookat") {
                opts.lookat = point3(x, y, z);
            }

            else if (key == "vup") {
                opts.vup = vec3(x, y, z);
            }
        }
    }

    return opts;
}

#endif
