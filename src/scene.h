#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

#include "ray.h"
#include "interval.h"
#include "intersection.h"
#include "material.h"
#include "area_light.h"
#include "sphere.h"
#include "triangle.h"

const auto MODE_DEPT = "dept";
const auto MODE_NORM = "norm";
const auto MODE_FULL = "full";

class scene {
    public:
        scene();

        void add_material(material& mtl);

        void add_vertex(const point3& vertex);
        void add_normal(const vec& normal);
        void add_polygon(std::vector<int> v_indexes, std::vector<int> vn_indexes, const std::string& name);
        void add_sphere(const point3& center, double radius, const std::string& name);

        void add_light(const point3& position, const color3& intensity);
        void add_area_light(const point3& position, const color3& intensity, const vec& u, const vec& v);

        color3 illuminance(const ray& camera_ray, int depth);

    private:
        bool hit_scene(const ray& ray, interval& interval, intersection& intersection);

        std::unordered_map<std::string, material>   materials;

        std::vector<point3>     vertices;
        std::vector<vec>        normales;
        std::vector<triangle>   triangles;
        std::vector<sphere>     spheres;

        std::vector<light>      lights;
        std::vector<area_light> area_lights;
};

#endif
