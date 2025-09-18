#ifndef RANDOM_H
#define RANDOM_H

#include <random>

inline double random_double(double min, double max) {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    return min + (max - min) * dist(gen);
}

#endif
