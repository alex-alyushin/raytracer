#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <random>

const double pi = 3.141592653589793;
const double infinity = std::numeric_limits<double>::infinity();

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double(double min, double max) {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    return min + (max - min) * dist(gen);
}

inline double random_double() {
    return random_double(0.0, 1.0);
}

#endif
