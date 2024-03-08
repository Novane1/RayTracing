#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
class vec3
{

public : 
    vec3() {}

    // Constructor with three floating-point values
    vec3(float el, float el2, float e3) {
        e[0] = el;
        e[1] = el2;
        e[2] = e3;
    }

    // Member functions to access the individual components
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    // Member functions to access components as color values
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    // Overload unary plus operator
    inline const vec3& operator+() const { return *this; }

    // Overload unary minus operator
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    // Overload square bracket operator
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3& operator+= (const vec3& v2);
    inline vec3& operator-= (const vec3& v2);
    inline vec3& operator*= (const vec3& v2);
    inline vec3& operator/= (const vec3& v2);
    inline vec3& operator*= (const float t);
    inline vec3& operator/= (const float t);

    inline float length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }
    inline float squared_length() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    inline void make_unit_vector();

    float e[3];
};

inline std::istream& operator >>(std::istream& is, vec3& t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator <<(std::ostream& os, const vec3& t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline void vec3::make_unit_vector() {
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}

inline vec3 operator+ (const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator- (const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator* (const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/ (const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/ ( const vec3& v, float t) {
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator* (const vec3& v, float t) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline float dot(const vec3& v1, const vec3& v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
	);
}

inline vec3& vec3::operator+=(const vec3& v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline vec3& vec3::operator*=(const vec3& v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline vec3& vec3::operator/=(const vec3& v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

inline vec3& vec3::operator-=(const vec3& v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

inline vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline vec3& vec3::operator/=(const float t) {
	float k = 1.0 / t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

inline vec3 unit_vector(vec3 v) {
	float l = v.length();
	return vec3(v.e[0] / l, v.e[1] / l, v.e[2] / l);
}


