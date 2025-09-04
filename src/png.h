#include <iostream>
#include <string>
#include <vector>

#include "color.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void create_png(const color3matrix& color_matrix, std::string output_file) {
    int width = color_matrix[0].size();
    int height = color_matrix.size();
    int channels = 3;

    std::vector<unsigned char> image_data(width * height * channels);

    for (int y = 0; y < height; y += 1) {
        for (int x = 0; x < width; x += 1) {
            int index = (y * width + x) * channels;

            const auto& pixel = color_matrix[y][x];

            image_data[index + 0] = static_cast<unsigned char>(pixel.x());
            image_data[index + 1] = static_cast<unsigned char>(pixel.y());
            image_data[index + 2] = static_cast<unsigned char>(pixel.z());
        }
    }

    int result = stbi_write_png(
        output_file.c_str(),
        width,
        height,
        channels,
        image_data.data(),
        width * channels
    );

    if (result) {
        std::cout << "[PNG] image created: " << output_file << std::endl;
    } else {
        std::cerr << "[PNG] failed to create PNG: " << output_file << std::endl;
    }
}
