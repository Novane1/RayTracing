#pragma once

#include "ray.h"

class camera {
public :

	vec3 origin;
	vec3 lower_left_corner;
	vec3 vertical;
	vec3 horizontal;

	camera() : origin(0.0, 0.0, 0.0), lower_left_corner(-2.0, -1.0, -1.0),
		horizontal(4.0, 0.0, 0.0), vertical(0.0, 2.0, 0.0) {}
	ray get_ray(float u, float v) { 
		ray rp(origin, lower_left_corner + u * horizontal + v * vertical); return rp; 
	}
	
	


};
