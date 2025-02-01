#ifndef MATERIAL_H
#define MATERIAL_H

#include <algorithm>

class material {
    public:
        virtual ~material() = default;
};


class lambertian : public material {
  public:
    lambertian(const color3& albedo) : albedo(albedo) {}

  private:
    color3 albedo;
};

class metal : public material {
  public:
    metal(const color3& albedo, double fuzz)
        : albedo(albedo)
        , fuzz(std::min(fuzz, 1.0)) {}

  private:
    color3 albedo;
    double fuzz;
};

class dielectric : public material {
  public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

  private:
    double refraction_index;
};

#endif
