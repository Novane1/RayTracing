#pragma once
#include <iostream>
#include <random>
#include "material.h"

vec3 random_in_unit_sphere() {
	vec3 p;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	do {
		p = 2.0 * vec3(dis(gen), dis(gen), dis(gen)) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;

}

class lambertian : public material {
public:
	vec3 albedo;
	lambertian(const vec3& a) : albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}

};

