#include <iostream>
#include <fstream>
#include <float.h>
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include <random>
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
using namespace std;

// Previous useful function
bool hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

float hit_sphere_float(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0*a);
	}

}


//End of this section
vec3 color(const ray& r,hitable *world, int depth) {

	hit_record rec;
	if (world->hit(r, 0.001,FLT_MAX , rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	
	}
	else{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		
		vec3 up = (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);

		return up;
	}
}

hitable* random_scene() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	int n = 500;
	hitable** list = new hitable * [n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) 
	{
		for (int b = -11; b < 11; b++) 
		{
			float choose_mat = dis(gen);
			vec3 center(a + 0.9 * dis(gen), 0.2, b + 0.9 * dis(gen));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) 
			{
				if (choose_mat < 0.8) {
					vec3 truc = vec3(dis(gen) * dis(gen), dis(gen) * dis(gen), dis(gen) * dis(gen));
					list[i++] = new sphere(center, 0.2, new lambertian(truc));
				}
				else if (choose_mat <  0.95) {
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1.0+dis(gen)), 0.5 * (1.0 + dis(gen)), 0.5 * (1.0 + dis(gen))), 0.5 * (1.0 + dis(gen))));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}

			}
		}
	}
	list[i++] = new sphere(vec3(0,1,0),1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4,0.2,0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5),0.0));
	cout << "World generated" << endl;
	return new hitable_list(list, i);
}

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	int nx = 2000;
	int ny = 1000;
	int ns = 10;
	ofstream outputFile("output.ppm");
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";
	
	/*float R = cos(PI / 4);
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));*/


	hitable* world = random_scene();

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 2;

	camera cam(lookfrom,lookat,vec3(0,1,0),90, float(nx) / float(ny),aperture, dist_to_focus);
	for (int j = ny - 1; j >= 0; j--) {
		cout << j << endl;
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i+ dis(gen)) / float(nx);
				float v = float(j+ dis(gen)) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world,0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			

			
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			
			outputFile << ir << " " << ig << " " << ib << endl;
			
		}
	}
	
	outputFile.close();
}