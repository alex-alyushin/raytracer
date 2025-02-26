#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "utils.h"

class vec3 {
    public:
        double e[3];

        vec3() : vec3(0, 0, 0) {}

        vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3 operator-() const {
            return vec3(-x(), -y(), -z());
        }

        vec3& operator+=(const vec3& v) {
            e[0] += v[0];
            e[1] += v[1];
            e[2] += v[2];

            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        vec3& operator/=(double t) {
            return *this *= 1 / t;
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        static vec3 random() {
            return vec3(
                random_double(),
                random_double(),
                random_double()
            );
        }

        static vec3 random(double min, double max) {
            return vec3(
                random_double(min, max),
                random_double(min, max),
                random_double(min, max)
            );
        }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x() << " " << v.y() << " " << v.z();
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1 / t) * v;
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline double dot(const vec3& v, const vec3& u) {
    return (
        v.x() * u.x() +
        v.y() * u.y() +
        v.z() * u.z()
    );
}

inline vec3 cross(const vec3& v, const vec3& u) {
    return vec3(
        v.y() * u.z() - v.z() * u.y(),
        v.z() * u.x() - v.x() * u.z(),
        v.x() * u.y() - v.y() * u.x()
    );
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(
            random_double(-1, 1),
            random_double(-1, 1),
            0
        );

        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, +1);
        auto lensq = p.length_squared();

        if (1e-160 < lensq && lensq <= 1.0)
            return p / sqrt(lensq);
    }
}

#endif
