#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <optional>

#include "ray.h"
#include "interval.h"
#include "intersection.h"
#include "material.h"
#include "sphere.h"
#include "light.h"
#include "area_light.h"

const auto MODE_DEPT = "dept";
const auto MODE_NORM = "norm";
const auto MODE_FULL = "full";

class scene {
    public:
        scene();

        color3 illuminance_v2(const ray& camera_ray, int depth);
        color3 illuminance_v1(const ray& camera_ray, std::string mode, int depth);

        // void add_vertex(const point3& position, int index);
        // void add_poligon(std::vector<const point3>& vertexes, const std::string& name);
        void add_sphere(const point3& center, double radius, const std::string& name);
        void add_area_light(const point3& position, const color3& intensity, const vec& u, const vec& v);
        void add_light(const point3& position, const color3& intensity);
        void add_material(std::shared_ptr<material> model);

    private:
        std::vector<std::shared_ptr<light>>         lights;
        std::vector<std::shared_ptr<area_light>>    area_lights;
        std::vector<std::shared_ptr<object>>        objects;
        std::unordered_map<std::string, std::shared_ptr<material>> materials;

        std::optional<intersection> hit(const ray& ray, const interval& interval);
        color3 get_sky(const ray& ray);
};

#endif
