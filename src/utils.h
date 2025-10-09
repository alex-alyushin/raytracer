#ifndef UTILS_H
#define UTILS_H

#include <random>

static const double pi = 3.141592653589793;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double(double min, double max) {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    return min + (max - min) * dist(gen);
}

#endif
