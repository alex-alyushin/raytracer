#ifndef MATERIAL_H
#define MATERIAL_H

#include <algorithm>

class material {
	public:
		virtual ~material() = default;
		virtual bool scatter(const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered) const = 0;
		virtual std::string type() = 0;
};

class lambertian : public material {
	public:
		lambertian(const color3& albedo) : albedo(albedo) {}

		std::string type() override {
			return "lambertian";
		}

		bool scatter(const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered) const override {
			auto scatter_direction = rec.normal + random_unit_vector();

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

	private:
		color3 albedo;
		double fuzz;
};

class dielectric : public material {
	public:
		dielectric(double refraction_index) : refraction_index(refraction_index) {}

	private:
		double refraction_index;
};

#endif
