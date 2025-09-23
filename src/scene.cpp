#include "scene.h"

const auto BLACK = color3(0.0, 0.0, 0.0);
const auto WHITE = color3(1.0, 1.0, 1.0);

scene::scene() {}

void scene::add_lamp(const point3& position, const color3& intensity) {
    lamps.push_back(
        std::make_shared<lamp>(
            position,
            intensity
        )
    );
}

void scene::add_sphere(const point3& center, double radius, const std::string& name) {
    objects.push_back(
        std::make_shared<sphere>(
            center,
            radius,
            materials[name]
        )
    );
}

void scene::add_material_model(std::shared_ptr<material_model> model) {
    materials[model->name] = model;
}

/*
void scene::add_material(std::shared_ptr<material_model> model, const std::string& material_name) {
    if (model->diffuse_color.length_squared() > 0.001) {
        materials[material_name] = std::make_shared<lambertian>(
            model->diffuse_color
        );
    }

    else if (model->specular_color.length_squared() > 0.001) {
        materials[material_name] = std::make_shared<metal>(
            model->specular_color,
            0.0
        );
    }

    else if ( Tr > 0 && Ni > 0) {
        // materials[material_name] = std::make_shared<dielectric>(
        //     1.3333
        // );
    }
}
*/

color3 scene::illuminance_v2(const ray& camera_ray, int depth) {
    if (depth < 0) {
        return BLACK;
    }

    color3 illum = color3(0.0, 0.0, 0.0);

    // Hit scene

    std::optional<hit_record> rec = hit_scene(camera_ray, interval{ 0.001 });

    if (!rec.has_value()) {
        return get_sky(camera_ray);
    }

    hit_record rec_value = rec.value();
    auto point = rec_value.point;

    auto specular_exponent  = rec_value.mat->specular_exponent;
    auto specular_color     = rec_value.mat->specular_color;
    auto diffuse_color      = rec_value.mat->diffuse_color;

    // Recursion

    auto specular_reflected = mirror_reflection(camera_ray.direction(), rec_value);

    if (specular_color.length_squared() > 0.001) {
        illum += 0.333 * specular_color * illuminance_v2(ray(point, specular_reflected), depth - 1);
    }

    // Main cycle by lamps

    for (auto lamp : lamps) {
        auto lamp_intensity = lamp->intensity;
        auto lamp_vec = lamp->position - point;
        auto lamp_ray = ray(point, lamp_vec);

        auto attenuation = [](double r) {
            return 1.0 / (1.0 + 0.22 * r + 0.20 * r * r);
        };

        std::optional<hit_record> shadow = hit_scene(lamp_ray, interval{ 0.001, lamp_vec.length() });

        if (shadow.has_value()) {
            continue;
        }

        if (specular_color.length_squared() > 0.001) {
            illum += attenuation(lamp_vec.length())
                * lamp_intensity
                * specular_color
                * std::pow(
                    std::max(
                        0.0,
                        dot(unit_vector(lamp_vec), specular_reflected)
                    ),
                    specular_exponent
                );
        }

        if (diffuse_color.length_squared() > 0.001) {
            illum += attenuation(lamp_vec.length())
                * lamp_intensity
                * diffuse_color
                * std::max(
                    0.0,
                    dot(unit_vector(lamp_vec), rec_value.normal)
                );
        }
    }

    return illum;
}

/*
color3 scene::illuminance(const ray& camera_ray, std::string mode, int depth) {
    if (depth < 0) {
        return get_sky(camera_ray);
    }

    auto rec = hit_scene(camera_ray, interval{0.001});

    if (!rec.has_value()) {
        return get_sky(camera_ray);
    }

    if (mode == MODE_DEPT) {
        double gray = std::exp(-rec.value().t);

        return color3(gray, gray, gray);
    }

    if (mode == MODE_NORM) {
        double R = (rec.value().normal.x() + 1.0) / 2;
        double G = (rec.value().normal.y() + 1.0) / 2;
        double B = (rec.value().normal.z() + 1.0) / 2;

        return color3(R, G, B);
    }

    if (mode == MODE_FULL) {
        ray scattered;
        color3 attenuation;

        if (rec.value().mat->scatter(camera_ray, rec.value(), attenuation, scattered)) {
            return attenuation * illuminance(scattered, mode, depth - 1);
        }

        return BLACK;
    }

    std::cerr << "[Render] unknown render mode: " << mode << std::endl;
    exit(1);
}
*/

std::optional<hit_record> scene::hit_scene(const ray& ray, const interval& interval) {
    std::optional<hit_record> rec = std::nullopt;

    for (auto object : objects) {
        auto new_record = object->hit(ray, interval);

        if (new_record.has_value()) {
            if (!rec.has_value() || new_record.value().t < rec.value().t) {
                rec = new_record;
            }
        }
    }

    return rec;
}

color3 scene::get_sky(const ray& ray) {
    auto unit_direction = unit_vector(ray.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);
}
