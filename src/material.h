#ifndef MATERIAL_H
#define MATERIAL_H

#include <algorithm>

#include "random.h"
#include "physics.h"

/*

Lambertian: diffuse
	Kd = albedo (the main surface color)

Metal: specular (mirror)
	Ks = metal color (specular reflection is tinted by the material color: gold – yellowish, copper – reddish, etc.)

Dielectric: refraction
	Kd = albedo (the color of the material that is scattered inside)
	Ks = a fixed small value (usually white reflection ~0.04)

*/

struct mtl_model {
    std::string name;

    color3 ambient_color        = color3(0, 0, 0);
    color3 diffuse_color        = color3(0, 0, 0);
    color3 specular_color       = color3(0, 0, 0);
    color3 intensity            = color3(0, 0, 0);
    color3 albedo               = color3(1, 0, 0);

    double specular_exponent;
    double refraction_index;
};

using mtl_models_t = std::unordered_map<std::string, std::shared_ptr<mtl_model>>;

class material {
	public:
		virtual ~material() = default;
		virtual bool scatter(
			const ray& ray_in,
			const hit_record& rec,
			color3& attenuation,
			ray& ray_out
		) const = 0;
};

using materials_t = std::unordered_map<std::string, std::shared_ptr<material>>;

class lambertian : public material {
	public:
		lambertian(const color3& albedo)
			: albedo(albedo) {}

		bool scatter(const ray& ray_in, const hit_record& rec, color3& attenuation, ray& ray_out) const override {
			auto reflected = diffuse_reflection(rec);

			ray_out = ray(rec.point, reflected);
			attenuation = albedo;

			return true;
		}

	private:
		color3 albedo;
};

class metal : public material {
	public:
		metal(const color3& albedo, double fuzz)
			: albedo(albedo)
			, fuzz(std::min(fuzz, 1.0)) {}

		bool scatter(const ray& ray_in, const hit_record& rec, color3& attenuation, ray& ray_out) const override {
			auto reflected = mirror_reflection(ray_in.direction(), rec) + fuzz * random_unit_vector();

			ray_out = ray(rec.point, reflected);
			attenuation = albedo;

			return dot(ray_out.direction(), rec.normal) > 0;
		}


	private:
		color3 albedo;
		double fuzz;
};

class dielectric : public material {
	public:
		dielectric(double refraction_index) : refraction_index(refraction_index) {}

		bool scatter(const ray& ray_in, const hit_record& rec, color3& attenuation, ray& ray_out) const override {
			auto refracted = refraction(ray_in.direction(), rec, refraction_index);

			ray_out = ray(rec.point, refracted);
			attenuation = albedo;

			return true;
		}

	private:
		color3 albedo = color3(1.0, 1.0, 1.0);
		double refraction_index;
};

#endif
