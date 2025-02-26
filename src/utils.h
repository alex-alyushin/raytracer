#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <random>

const double pi = 3.141592653589793;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);

    return dist(gen);
}

inline double random_double() {
    return random_double(0.0, 1.0);
}

std::pair<std::string, std::string> parse_arguments(const std::string& arg) {
    size_t pos = arg.find('=');

    if (pos != std::string::npos) {
        std::string key = arg.substr(0, pos);
        std::string value = arg.substr(pos + 1);
        size_t key_pos = key.find("--");

        if (key_pos != std::string::npos) {
            key = key.substr(key_pos + 2);
            return std::pair<std::string, std::string>(key, value);
        }
    }

    return std::pair<std::string, std::string>();
}

#endif
