#ifndef MATERIAL_H
#define MATERIAL_H

class material_model {
    public:
        std::string name;
        color3 ambient_color        = color3(0, 0, 0);
        color3 ambient_color_e      = color3(0, 0, 0);
        color3 diffuse_color        = color3(0, 0, 0);
        color3 specular_color       = color3(0, 0, 0);
        color3 albedo               = color3(1, 0, 0);
        double specular_exponent;
        double refraction_index;
};

#endif
