#include <vector>

std::vector<std::vector<std::tuple<int, int, int>>> StabImage() {
    const int image_width = 1024;
    const int image_height = 720;

    std::vector<std::vector<std::tuple<int, int, int>>> color_matrix;

    for (size_t height = 0; height < image_height; height += 1) {
        std::vector<std::tuple<int, int, int>> color_row;

        for (size_t width = 0; width < image_width; width += 1) {
            const int channel = 256 * (height + width) / (image_height + image_width);

            int R = 255;
            int G = channel;
            int B = 255 - channel;

            color_row.push_back({ R, G, B });
        }

        color_matrix.push_back(color_row);
    }

    return color_matrix;
}

std::string StabOutput() {
    return "stab_image.png";
}
