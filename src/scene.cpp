#include "scene.h"

const auto BLACK = color3(0.0, 0.0, 0.0);
const auto WHITE = color3(1.0, 1.0, 1.0);

scene::scene() {}

void scene::add_light(const point3& position, const color3& intensity) {
    light light(position, intensity);
    lights.push_back(light);
}

void scene::add_area_light(const point3& position, const color3& intensity, const vec& u, const vec& v) {
    area_light area_light(position, intensity, u, v);
    area_lights.push_back(area_light);
}

void scene::add_material(material& mtl) {
    materials.insert({mtl.name, mtl});
}

void scene::add_vertex(const point3& vertex) {
    vertices.push_back(vertex);
}

void scene::add_normal(const vec& normal) {
    normales.push_back(normal);
}

void scene::add_polygon(std::vector<int> v_indexes, std::vector<int> vn_indexes, const std::string& name) {

    auto pos = [] (int size, int ind) {
        return ind > 0 ? (ind - 1) : (ind + size);
    };

    for (int index = 1; index <= v_indexes.size() - 2; index += 1) {
        triangles.emplace_back(
            vertices[pos(vertices.size(), v_indexes[0])],
            vertices[pos(vertices.size(), v_indexes[index])],
            vertices[pos(vertices.size(), v_indexes[index + 1])],

            normales[pos(normales.size(), vn_indexes[0])],
            normales[pos(normales.size(), vn_indexes[index])],
            normales[pos(normales.size(), vn_indexes[index + 1])],

            &materials.at(name)
        );
    }
}

void scene::add_sphere(const point3& center, double radius, const std::string& name) {
    spheres.emplace_back(
        center,
        radius,
        &materials.at(name)
    );
}

color3 scene::illuminance(const ray& camera_ray, int depth) {
    color3 illum = color3(0.0, 0.0, 0.0);

    if (depth < 0) {
        return illum;
    }

    intersection scene_intersection;

    if (!hit_scene(camera_ray, interval{ 0.001 }, scene_intersection)) {
        return illum;
    }

    auto point              = scene_intersection.point;
    auto ambient_color      = scene_intersection.mat->ambient_color;
    auto emissive_color     = scene_intersection.mat->emissive_color;
    auto specular_exponent  = scene_intersection.mat->specular_exponent;
    auto specular_color     = scene_intersection.mat->specular_color;
    auto diffuse_color      = scene_intersection.mat->diffuse_color;

    for (auto area_light : area_lights) {
        for (auto light : area_light.sample()) {
            // @todo: move it to class light
            auto lamp_intensity = light.intensity;
            auto lamp_vec = light.position - point;
            auto lamp_ray = ray(point, unit_vector(lamp_vec));

            auto R = lamp_vec.length();
            auto attenuation = 1.0 / (1.0 + 0.22 * R + 0.20 * R * R);

            intersection shadow;
            if (hit_scene(lamp_ray, interval{ 0.001, R }, shadow)) {
                continue;
            }

            if (ambient_color.length_squared() > 0.001) {
                illum += ambient_color;
            }

            if (emissive_color.length_squared() > 0.001) {
                illum += emissive_color;
            }

            if (specular_color.length_squared() > 0.001) {
                auto reflected = scene_intersection.get_specular_reflected(camera_ray);

                illum += attenuation
                    * lamp_intensity
                    * specular_color
                    * std::pow(
                        std::max(0.0, dot(lamp_ray.direction(), reflected.direction())),
                        specular_exponent
                    );
            }

            if (diffuse_color.length_squared() > 0.001) {
                illum += attenuation
                    * lamp_intensity
                    * diffuse_color
                    * std::max(0.0, dot(lamp_ray.direction(), scene_intersection.normal));
            }
        }
    }

    // Recursion
    if (specular_color.length_squared() > 0.001) {
        illum += 0.333 * specular_color * illuminance(scene_intersection.get_specular_reflected(camera_ray), depth - 1);
    }

    return illum;
}

bool scene::hit_scene(const ray& ray, const interval& i, intersection& intersection) {
    double dist = i.max;
    bool found = false;

    for (auto object : spheres) {
        if (object.hit(ray, interval{ i.min, dist }, intersection)) {
            found = true;
            dist = i.max;
        }
    }

    for (auto object : triangles) {
        if (object.hit(ray, interval{ i.min, dist }, intersection)) {
            found = true;
            dist = i.max;
        }
    }

    return found;
}
