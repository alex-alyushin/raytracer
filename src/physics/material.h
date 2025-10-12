#ifndef MATERIAL_H
#define MATERIAL_H

class material {
    public:
        material(const std::string& name)
            : name(name)
            , ambient_color(color3(0, 0, 0))
            , emissive_color(color3(0, 0, 0))
            , diffuse_color(color3(0, 0, 0))
            , specular_color(color3(0, 0, 0))
            , albedo(color3(1, 0, 0))
            , specular_exponent(0)
            , refraction_index(0) {}

        std::string name;
        color3 ambient_color;
        color3 emissive_color;
        color3 diffuse_color;
        color3 specular_color;
        color3 albedo;
        double specular_exponent;
        double refraction_index;
};

#endif
