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

const auto MODE_DEPT = "dept";
const auto MODE_NORM = "norm";
const auto MODE_FULL = "full";

class scene {
    public:
        scene();
        void add_sphere(const point3& center, double radius, const std::string& material_name);
        void add_material(std::shared_ptr<material_model> model, const std::string& material_name);
        color3 illuminance(const ray& camera_ray, std::string mode, int depth);

    private:
        std::vector<std::shared_ptr<hittable>>                      objects;
        std::unordered_map<std::string, std::shared_ptr<material>>  materials;
        std::optional<hit_record>   hit_scene(const ray& ray, const interval& interval);
        color3                      get_sky(const ray& ray);
};

#endif
