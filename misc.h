#pragma once
#include "vec2.h"
#include "vec3.h"
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

inline vec3 norm(vec3 const &v) { return (v / length(v)); }

vec2 sphere(vec3 ro, vec3 rd, float r);

} // namespace myMisc
