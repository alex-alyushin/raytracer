#ifndef MATERIAL_H
#define MATERIAL_H

#include <algorithm>
#include "physics.h"

/*

Lambertian: diffuse
	Kd = albedo (the main surface color)
	Ka = ambient lighting
	Ks = 0

Metal: specular (mirror)
	Ks = metal color (specular reflection is tinted by the material color: gold – yellowish, copper – reddish, etc.)
	Ka = 0 (not used)
	Kd = 0

Dielectric: refraction
	Kd = albedo (the color of the material that is scattered inside)
	Ks = a fixed small value (usually white reflection ~0.04)
	Ka ≈ not used

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
			const ray& r_in,
			const hit_record& rec,
			color3& attenuation,
			ray& scattered
		) const = 0;
};

using materials_t = std::unordered_map<std::string, std::shared_ptr<material>>;

class lambertian : public material {
	public:
		lambertian(const color3& albedo)
			: albedo(albedo) {}

		bool scatter(const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered) const override {
			auto scatter_direction = diffuse_reflected_vec(rec.normal);

			if (scatter_direction.near_zero()) {
				std::cout << "near zero" << std::endl;
			}

			scattered = ray(rec.point, scatter_direction);
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

		bool scatter(const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered) const override {
			auto reflected = specular_reflected_vec(r_in.direction(), rec.normal);
				+ fuzz * random_unit_vector();

			scattered = ray(rec.point, reflected);
			attenuation = albedo;

			// @todo: check it before calculating reflections
			return dot(scattered.direction(), rec.normal) > 0;
		}


	private:
		color3 albedo;
		double fuzz;
};

class dielectric : public material {
	public:
		dielectric(double refraction_index) : refraction_index(refraction_index) {}

		bool scatter(const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered) const override {
			double ri = rec.front_face
				? (1.0 / refraction_index)
				: refraction_index;

			auto unit_direction = unit_vector(r_in.direction());
			double cos = std::fmin(dot(-unit_direction, rec.normal), 1.0);
			double sin = std::sqrt(1.0 - cos * cos);

			bool cannot_refract = ri * sin > 1.0;
			vec3 direction;

			if (cannot_refract || reflectance(cos, ri) > random_double()) {
				direction = specular_reflected_vec(unit_direction, rec.normal);
			} else {
				direction = refracted_vec(unit_direction, rec.normal, ri);
			}

			scattered = ray(rec.point, direction);
			attenuation = color3(1.0, 1.0, 1.0);

			return true;
		}

	private:
		double refraction_index;

		static double reflectance(double cos, double refraction_index) {
			auto R = (1 - refraction_index) / (1 + refraction_index);
			R = R * R;

			return R + (1 - R) * std::pow((1 - cos), 5);
		}
};

#endif
