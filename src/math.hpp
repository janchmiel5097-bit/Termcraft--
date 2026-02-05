#pragma once

#include <complex>
float lerp(float a, float b, float t) {
    return a + ((b - a) * t);
}

struct vec2 {
    explicit vec2 (
        float _x=0.0F,
        float _y=0.0F
    ): x(_x), y(_y) {}
    float x=0.0F,y=0.0F;

    vec2 operator+(const vec2& o) const { return vec2(x + o.x, y + o.y); }
    vec2 operator-(const vec2& o) const { return vec2(x - o.x, y - o.y); }
    vec2 operator*(const float& f) const { return vec2(x * f, y * f); }
    vec2 operator/(const float& f) const { return vec2(x / f, y / f); }
    vec2& operator+=(const vec2& o) { x += o.x; y += o.y; return *this; }
    vec2& operator*=(const float& f) { x *= f; y *= f; return *this; }
};

struct vec4 {
    explicit vec4 (
        float _r=0.0F,
        float _g=0.0F,
        float _b=0.0F,
        float _a=0.0F
    ): r(_r), g(_g), b(_b), a(_a) {}

    explicit vec4 (
        int hex
    ) : r(((hex >> 24) & 0xFF) / 255.0F), g(((hex >> 16) & 0xFF) / 255.0F),
        b(((hex >>  8) & 0xFF) / 255.0F), a(((hex      ) & 0xFF) / 255.0F) {}

    float r=0.0F,g=0.0F,b=0.0F,a=0.0F;
};
