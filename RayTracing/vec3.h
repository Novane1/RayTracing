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

