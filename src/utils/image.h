#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <vector>

#include "interval.h"
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

class image {
    public:
        static inline void write_to_png(const color3matrix& color_matrix, std::string output_file);
        static inline color3 intensity_to_color(const color3& color);

    private:
        static inline double linear_to_gamma(double linear);
};

void image::write_to_png(const color3matrix& color_matrix, std::string output_file) {
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
        std::cout << "[Image] image created: " << output_file << std::endl;
    } else {
        std::cerr << "[Image] failed to create PNG: " << output_file << std::endl;
    }
}

color3 image::intensity_to_color(const color3& color) {
    auto R = color.x();
    auto G = color.y();
    auto B = color.z();

    // Gamma correction
    R = image::linear_to_gamma(R);
    G = image::linear_to_gamma(G);
    B = image::linear_to_gamma(B);

    // In [0, 1]
    static const interval value(0.000, 0.999);

    auto rByte = int(256 * value.clamp(R));
    auto gByte = int(256 * value.clamp(G));
    auto bByte = int(256 * value.clamp(B));

    return color3(rByte, gByte, bByte);
}

double image::linear_to_gamma(double linear) {
    if (linear > 0) {
        return std::sqrt(linear);
    }

    return 0;
}

#endif
