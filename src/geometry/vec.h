#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <iostream>

#include "utils.h"

class vec {
    public:
        double e[3];

        vec() : vec(0, 0, 0) {}

        vec(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec operator-() const {
            return vec(-x(), -y(), -z());
        }

        vec& operator+=(const vec& v) {
            e[0] += v[0];
            e[1] += v[1];
            e[2] += v[2];

            return *this;
        }

        vec& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        vec& operator/=(double t) {
            return *this *= 1 / t;
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        bool near_zero() {
            auto delta = 1e-8;

            return (std::fabs(e[0]) < delta)
                && (std::fabs(e[1]) < delta)
                && (std::fabs(e[2]) < delta);
        }

        static vec random(double min, double max) {
            return vec(
                random_double(min, max),
                random_double(min, max),
                random_double(min, max)
            );
        }
};

/***********/
/* Aliases */
/***********/

using point3        = vec;
using color3        = vec;
using color3matrix  = std::vector<std::vector<color3>>;

/********************/
/* Binary operators */
/********************/

inline std::ostream& operator<<(std::ostream& out, const vec& v) {
    return out << v.x() << " " << v.y() << " " << v.z();
}

inline vec operator+(const vec& u, const vec& v) {
    return vec(
        u.x() + v.x(),
        u.y() + v.y(),
        u.z() + v.z()
    );
}

inline vec operator-(const vec& u, const vec& v) {
    return vec(
        u.x() - v.x(),
        u.y() - v.y(),
        u.z() - v.z()
    );
}

inline vec operator*(const vec& u, const vec& v) {
    return vec(
        u.x() * v.x(),
        u.y() * v.y(),
        u.z() * v.z()
    );
}

inline vec operator*(double t, const vec& v) {
    return vec(t * v.x(), t * v.y(), t * v.z());
}

inline vec operator*(const vec& v, double t) {
    return t * v;
}

inline vec operator/(const vec& v, double t) {
    return (1 / t) * v;
}

inline vec unit_vector(const vec& v) {
    if (v.length() == 0) {
        return v;
    }

    return v / v.length();
}

inline double dot(const vec& v, const vec& u) {
    return (
        v.x() * u.x() +
        v.y() * u.y() +
        v.z() * u.z()
    );
}

inline vec cross(const vec& v, const vec& u) {
    return vec(
        v.y() * u.z() - v.z() * u.y(),
        v.z() * u.x() - v.x() * u.z(),
        v.x() * u.y() - v.y() * u.x()
    );
}

/******************/
/* Random vectors */
/******************/

inline vec random_in_unit_square() {
    return vec(
        random_double(-1, 1),
        random_double(-1, 1),
        0
    );
}

inline vec random_in_unit_disk() {
    while (true) {
        auto p = random_in_unit_square();

        if (p.length_squared() < 1)
            return p;
    }
}

inline vec random_unit_vector() {
    while (true) {
        auto p = vec::random(-1, +1);
        auto lensq = p.length_squared();

        if (1e-160 < lensq && lensq <= 1.0)
            return p / sqrt(lensq);
    }
}

inline vec random_on_hemisphere(const vec& normal) {
    vec on_unit_sphere = random_unit_vector();

    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    }

    return -on_unit_sphere;
}

#endif
