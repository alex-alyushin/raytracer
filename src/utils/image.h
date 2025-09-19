#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"

class image {
    public:
        image(color3matrix& matrix)
            : matrix(matrix) {}

        void post_processing();
        void store(const std::string& output_file);

    private:
        color3matrix& matrix;
};

inline double gamma_correction(double linear) {
    if (linear > 0) {
        return std::sqrt(linear);
    }

    return 0;
}

void image::post_processing() {
    for (int i = 0; i < matrix.size(); i += 1) {
        for (int j = 0; j < matrix[0].size(); j += 1) {
            color3 color = matrix[i][j];

            auto R = color.x();
            auto G = color.y();
            auto B = color.z();

            R = gamma_correction(R);
            G = gamma_correction(G);
            B = gamma_correction(B);

            auto rByte = int(256 * std::min(0.999, R));
            auto gByte = int(256 * std::min(0.999, G));
            auto bByte = int(256 * std::min(0.999, B));

            matrix[i][j] = color3(rByte, gByte, bByte);
        }
    }
}

void image::store(const std::string& output_file) {
    int width = matrix[0].size();
    int height = matrix.size();
    int channels = 3;

    std::vector<unsigned char> image_data(width * height * channels);

    for (int y = 0; y < height; y += 1) {
        for (int x = 0; x < width; x += 1) {
            int index = (y * width + x) * channels;

            const auto& pixel = matrix[y][x];

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

#endif
