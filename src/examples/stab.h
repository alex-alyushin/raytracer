#include "color.h"

color3matrix StabImage() {
    color3matrix color_matrix;

    const int image_width = 1024;
    const int image_height = 720;

    for (size_t height = 0; height < image_height; height += 1) {
        std::vector<color3> color_row;

        for (size_t width = 0; width < image_width; width += 1) {
            const double channel = 256 * (height + width) / (image_height + image_width);

            auto R = 255;
            auto G = channel;
            auto B = 255 - channel;

            color_row.push_back(color3(R, G, B));
        }

        color_matrix.push_back(color_row);
    }

    return color_matrix;
}
