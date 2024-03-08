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

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b - 4 * a * c)) / a;
		if (temp<t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = unit_vector((rec.p - center) / radius);	
			/*if (rec.normal.x() < -1) {
				cout << rec.p << " " << center << endl;
			}*/
			return true;
		}
		temp = (-b + sqrt(b * b - 4 * a * c)) / a;
		if (temp<t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = unit_vector((rec.p - center) / radius);
			
			return true;
		}
	}
	return false;
}