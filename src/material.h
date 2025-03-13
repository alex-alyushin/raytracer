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
		lambertian(const color3& albedo)
			: albedo(albedo) {}

		std::string type() override {
			return "lambertian";
		}

		bool scatter(const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered) const override {
			auto scatter_direction = rec.normal + random_unit_vector();

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

		std::string type() override {
			return "metal";
		}

		bool scatter(const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered) const override {
			auto reflected = unit_vector(mirror_reflect(r_in.direction(), rec.normal));
				+ fuzz * random_unit_vector();

			scattered = ray(rec.point, reflected);
			attenuation = albedo;

			return dot(scattered.direction(), rec.normal) > 0;
		}


	private:
		color3 albedo;
		double fuzz;
};

class dielectric : public material {
	public:
		dielectric(double refraction_index) : refraction_index(refraction_index) {}

		std::string type() override {
			return "dielectric";
		}

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
				direction = mirror_reflect(unit_direction, rec.normal);
			} else {
				direction = refract_by_snell(unit_direction, rec.normal, ri);
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
