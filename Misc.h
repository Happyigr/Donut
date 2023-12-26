#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include <math.h>

namespace myMisc {

inline float clamp(float value, float min, float max) {
  return fmax(fmin(value, max), min);
}

inline float length(vec2 const &v) { return sqrt(v.x * v.x + v.y * v.y); }
inline float length(vec3 const &v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float dot(vec3 const &a, vec3 const &b) {
  return (a.x * b.x + a.y * b.y + a.z * b.z);
}
inline vec3 abs(vec3 const &v) { return vec3(fabs(v.x), fabs(v.y), fabs(v.z)); }
inline vec3 norm(vec3 const &v) { return (v / length(v)); }

inline double sign(double a) { return (0 < a) - (a < 0); }
inline vec3 sign(vec3 const &v) {
  return vec3(sign(v.x), sign(v.y), sign(v.z));
}

inline double step(double edge, double x) { return x > edge; }
inline vec3 step(vec3 const &edge, vec3 v) {
  return vec3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z));
}
inline vec3 reflect(vec3 rd, vec3 n) { return rd - n * (2 * dot(n, rd)); }

vec3 rotateX(vec3 a, double angle);
vec3 rotateY(vec3 a, double angle);
vec3 rotateZ(vec3 a, double angle);

vec2 sphere(vec3 camPos, vec3 dirRay, float r);
vec2 box(vec3 ro, vec3 rd, vec3 boxSize, vec3 &outNormal);
float plane(vec3 ro, vec3 rd, vec3 p, float w);
} // namespace myMisc
