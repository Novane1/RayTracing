#pragma once
#include <iostream>

#include "hitable.h"
using namespace std;
class sphere : public hitable {
public : 
	vec3 center;
	float radius;
	sphere() {};
	sphere(vec3 cen, float r) : center(cen), radius(r) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const { //Error in the page 16 for the discriminant. It is not but why?
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b -  a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b -  a * c)) / a;
		if (temp<t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);

			rec.normal = unit_vector((rec.p - center) );

			return true;
		}
		temp = (-b + sqrt(b * b - 4 * a * c)) / a;
		if (temp<t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = unit_vector((rec.p - center) );
			return true;
		}
	}
	return false;
}