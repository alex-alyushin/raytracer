#include <iostream>
#include <string>
#include <vector>

#include <pybind11/embed.h>
#include "color.h"

//==============================================================================================
// This C++ code init Python interpreter and run Python code in try/catch.
// Import Python module Pillow. Fill matrix in for-in-for cycle.
//
// Using to generate output .png file
//==============================================================================================

void create_png(const color3matrix& color_matrix, std::string output_file) {
    // init interpreter
    pybind11::scoped_interpreter guard{};

    try {
        pybind11::module_ image_module = pybind11::module_::import("pillow_image_generator");

        if (!image_module) {
            throw std::runtime_error("can\'t import module pillow_image_generator");
        } else {
            std::string module_name = image_module.attr("__name__").cast<std::string>();
            std::cout << "module loaded: " << module_name << std::endl;
        }

        pybind11::list matrix;

        for (const auto& row : color_matrix) {
            pybind11::list line;

            for (const auto& pixel : row) {
                line.append(pybind11::make_tuple(
                    pixel.x(),
                    pixel.y(),
                    pixel.z()
                ));
            }

            matrix.append(line);
        }

        image_module.attr("pillow_generate_image")(matrix, output_file);
    } catch (const pybind11::error_already_set& e) {
        std::cerr << "Python Error: " << e.what() << std::endl;
    }
}
