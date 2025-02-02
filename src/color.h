#ifndef COLOR_H
#define COLOR_H

#include <vector>

#include "interval.h"
#include "vec3.h"

// Aliases

using color3 = vec3;
using color3matrix = std::vector<std::vector<color3>>;

// Utils

inline double linear_to_gamma(double linear) {
    if (linear > 0) {
        return std::sqrt(linear);
    }

    return 0;
}

inline std::ostream& write_pixel(std::ostream& out, const color3& color) {
    auto R = color.x();
    auto G = color.y();
    auto B = color.z();

    // Gamma correction
    R = linear_to_gamma(R);
    G = linear_to_gamma(G);
    B = linear_to_gamma(B);

    // Transform from [0, 1] to [0, 255]
    static const interval value(0.000, 0.999);

    auto rByte = int(256 * value.clamp(R));
    auto gByte = int(256 * value.clamp(G));
    auto bByte = int(256 * value.clamp(B));

    return out << rByte << " " << gByte << " " << bByte;
}

#endif
