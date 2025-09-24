#ifndef HITTABLE_VECTOR_H
#define HITTABLE_VECTOR_H

#include <vector>
#include <memory>
#include <optional>

#include "ray.h"
#include "interval.h"
#include "hit_record.h"
#include "sphere.h"

#include "material.h"
#include "lamp.h"

const auto MODE_DEPT = "dept";
const auto MODE_NORM = "norm";
const auto MODE_FULL = "full";

class scene {
    public:
        scene();

        color3 illuminance_v2(const ray& camera_ray, int depth);
        color3 illuminance_v1(const ray& camera_ray, std::string mode, int depth);

        void add_lamp(const point3& position, const color3& intensity);
        void add_material_model(std::shared_ptr<material_model> model);
        void add_sphere(const point3& center, double radius, const std::string& name);
        // void add_poligon(std::vector<const point3>& vertexes, const std::string& name);
        // void add_vertex(const point3& position, int index);

    private:
        std::vector<std::shared_ptr<lamp>> lamps;
        std::vector<std::shared_ptr<hittable>> objects;
        std::unordered_map<std::string, std::shared_ptr<material_model>> materials;

        std::optional<hit_record> hit_scene(const ray& ray, const interval& interval);
        color3 get_sky(const ray& ray);
};

#endif
