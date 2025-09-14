#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class reader {
    public:
        static std::shared_ptr<collection> read_objects(const std::string& filename);
        static camera_opts read_camera_opts(const std::string& filename);
    private:
        static materials_t read_materials(const std::string& filename);
};

std::shared_ptr<collection> reader::read_objects(const std::string& filename) {
    std::cout << "[obj] reading file: " << filename << std::endl;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[obj] cannot read objects" << std::endl;
        exit(1);
    }

    auto scene = std::make_shared<collection>();

    std::shared_ptr<material> current_material = nullptr;
    materials_t materials;

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

            if (tokens[0] == "mtllib") {
                if (tokens.size() != 2) {
                    continue;
                }

                materials = read_materials(tokens[1]);
            }

            if (tokens[0] == "usemtl") {
                if (tokens.size() != 2) {
                    continue;
                }

                current_material = materials[tokens[1]];
            }

            // Sphere
            if (tokens[0] == "S") {
                if (tokens.size() != 5) {
                    continue;
                }

                scene->add(std::make_shared<sphere>(
                    point3(
                        std::stod(tokens[1]),   // x
                        std::stod(tokens[2]),   // y
                        std::stod(tokens[3])    // z
                    ),
                    std::stod(tokens[4]),       // radius
                    current_material
                ));
            }

            // Vertex
            if (tokens[0] == "v") {}

            // Vertex normale
            if (tokens[0] == "vn") {}

            // Vertex texture
            if (tokens[0] == "vt") {}

            // Face
            if (tokens[0] == "f") {}

            // Lighter
            if (tokens[0] == "P") {}
        }
    }

    file.close();

    return scene;
}

materials_t reader::read_materials(const std::string& filename) {
    std::cout << "[mtl] reading file: " << filename << std::endl;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[mtl] cannot read materials" << std::endl;
        exit(1);
    }

    std::shared_ptr<mtl_model> current_model = nullptr;
    mtl_models_t mtl_models;
    materials_t materials;

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

            if (tokens[0] == "newmtl") {
                std::string name = tokens[1];
                current_model = std::make_shared<mtl_model>();
                current_model->name = name;
                mtl_models[name] = current_model;
            }

            if (tokens[0] == "Ka") {
                current_model->ambient_color = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            if (tokens[0] == "Kd") {
                current_model->diffuse_color = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            if (tokens[0] == "Ks") {
                current_model->specular_color = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            if (tokens[0] == "Ke") {
                current_model->intensity = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            // @todo: implement
            // Ns (specular_exponent)
            // Ni (refraction_index)
            // al (abledo)
        }
    }

    file.close();

    for (auto& [ name, model ] : mtl_models) {
        std::shared_ptr<material> mat;

        /* Lambertian */
        if (model->diffuse_color.length_squared() > 0.001) {
            mat = std::make_shared<lambertian>(
                model->diffuse_color
            );
        }

        /* Metal */
        else if (model->specular_color.length_squared() > 0.001) {
            mat = std::make_shared<metal>(
                model->specular_color,
                0.0
            );
        }

        /* Dielectric */
        else if (false/* Tr > 0 && Ni > 0 */) {
        }

        else {
        }

        materials[name] = mat;
    }

    return materials;
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
