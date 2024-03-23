#pragma once

#include "ray.h"
#include <iostream>
#include <fstream>
#include <random>
const double PI = 3.14159265358979323846;

vec3 random_in_unit_disk() {
	vec3 p;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	do {
		p = 2.0 * vec3(dis(gen),dis(gen),0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1);
	return p;
}
class camera {
public :

	vec3 origin;
	vec3 lower_left_corner;
	vec3 vertical;
	vec3 horizontal;
	float lens_radius;
	vec3 u, v, w;

	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
		
		lens_radius = aperture/2;
		float theta = vfov * PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = vec3(-half_width, -half_height, -1.0);
		lower_left_corner = origin - half_width * focus_dist* u - half_height *focus_dist* v - focus_dist*w;
		horizontal = 2*half_width* focus_dist*u;
		vertical = 2 * half_height * focus_dist* v;
		
	}

		
	ray get_ray(float s, float t) { 
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray( origin+offset, lower_left_corner + s*horizontal + t * vertical - origin - offset); 
	}
	
	


};
