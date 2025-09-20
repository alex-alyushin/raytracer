#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "scene.h"

class scene_reader {
    public:
        static void read(scene& scene, const std::string& filename);
    private:
        static void read_materials(scene& scene, const std::string& filename);
};

void scene_reader::read(scene& scene, const std::string& filename) {
    std::cout << "[FileReader] reading obj file: " << filename << std::endl;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[FileReader] cannot read obj file" << std::endl;
        exit(1);
    }

    std::string material_name;
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

                read_materials(scene, tokens[1]);
            }

            if (tokens[0] == "usemtl") {
                if (tokens.size() != 2) {
                    continue;
                }

                material_name = tokens[1];
            }

            if (tokens[0] == "S") {
                if (tokens.size() != 5) {
                    continue;
                }

                scene.add_sphere(
                    point3(
                        std::stod(tokens[1]),   // x
                        std::stod(tokens[2]),   // y
                        std::stod(tokens[3])    // z
                    ),
                    std::stod(tokens[4]),       // radius
                    material_name               // material
                );
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
}

void scene_reader::read_materials(scene& scene, const std::string& filename) {
    std::cout << "[FileReader] reading mtl file: " << filename << std::endl;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[FileReader] cannot read mtl file" << std::endl;
        exit(1);
    }

    std::string current_name;
    std::unordered_map<std::string, std::shared_ptr<material_model>> material_models;
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
                current_name = tokens[1];
                material_models[current_name] = std::make_shared<material_model>();
                material_models[current_name]->name = current_name;
            }

            if (tokens[0] == "Ka") {
                material_models[current_name]->ambient_color = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            if (tokens[0] == "Kd") {
                material_models[current_name]->diffuse_color = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            if (tokens[0] == "Ks") {
                material_models[current_name]->specular_color = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            if (tokens[0] == "Ke") {
                material_models[current_name]->intensity = color3(
                    std::stod(tokens[1]),
                    std::stod(tokens[2]),
                    std::stod(tokens[3])
                );
            }

            // @todo: implement also
            // Ns (specular_exponent)
            // Ni (refraction_index)
            // al (abledo)
        }
    }

    file.close();

    for (auto& [ name, model ] : material_models) {
        scene.add_material(model, name);
    }
}

#endif
