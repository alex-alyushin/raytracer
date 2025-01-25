#include <iostream>
#include <string>
#include <vector>

#include <pybind11/embed.h>

#include "color.h"

void create_png(
    const color3matrix& color_matrix,
    std::string output_file
) {
    // init python interpreter
    pybind11::scoped_interpreter guard{};

    try {
        pybind11::module_ image_module = pybind11::module_::import("Pillow_Image_Generator");
        pybind11::list py_array;

        for (const auto& row : color_matrix) {
            pybind11::list py_row;

            for (const auto& pixel : row) {
                py_row.append(pybind11::make_tuple(
                    pixel.x(),
                    pixel.y(),
                    pixel.z()
                ));
            }

            py_array.append(py_row);
        }

        image_module.attr("generate_image")(py_array, output_file);
    } catch (const pybind11::error_already_set& e) {
        std::cerr << "Python Error: " << e.what() << std::endl;
    }
}
