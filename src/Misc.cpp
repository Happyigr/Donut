#include "Misc.h"

myMisc::vec3 myMisc::rotateX(myMisc::vec3 a, double angle) {
  myMisc::vec3 b = a;
  b.z = a.z * cos(angle) - a.y * sin(angle);
  b.y = a.z * sin(angle) + a.y * cos(angle);
  return b;
}

myMisc::vec3 myMisc::rotateY(myMisc::vec3 a, double angle) {
  myMisc::vec3 b = a;
  b.x = a.x * cos(angle) - a.z * sin(angle);
  b.z = a.x * sin(angle) + a.z * cos(angle);
  return b;
}

myMisc::vec3 myMisc::rotateZ(myMisc::vec3 a, double angle) {
  myMisc::vec3 b = a;
  b.x = a.x * cos(angle) - a.y * sin(angle);
  b.y = a.x * sin(angle) + a.y * cos(angle);
  return b;
}
myMisc::vec2 myMisc::sphere(myMisc::vec3 camPos, myMisc::vec3 dirRay, float r) {
  // angle between camPos and dirRay
  float b = myMisc::dot(camPos, dirRay);
  // distance between camera and sphere
  float c = myMisc::dot(camPos, camPos) - r * r;
  // ?
  float h = b * b - c;
  if (h < 0.0)
    return myMisc::vec2(-1.0);
  h = sqrt(h);
  return myMisc::vec2(-b - h, -b + h);
}

myMisc::vec2 myMisc::box(myMisc::vec3 ro, myMisc::vec3 rd, myMisc::vec3 boxSize,
                         myMisc::vec3 &outNormal) {
  myMisc::vec3 m = myMisc::vec3(1.0) / rd;
  myMisc::vec3 n = m * ro;
  myMisc::vec3 k = abs(m) * boxSize;
  myMisc::vec3 t1 = -n - k;
  myMisc::vec3 t2 = -n + k;
  float tN = fmax(fmax(t1.x, t1.z), t1.y);
  float tF = fmin(fmin(t2.x, t2.z), t2.y);
  if (tN > tF || tF < 0.0)
    return myMisc::vec2(-1.0);
  myMisc::vec3 yzx = myMisc::vec3(t1.y, t1.z, t1.x);
  myMisc::vec3 zxy = myMisc::vec3(t1.z, t1.x, t1.y);
  outNormal = -sign(rd) * step(yzx, t1) * step(zxy, t1);
  return myMisc::vec2(tN, tF);
}

float myMisc::plane(myMisc::vec3 ro, myMisc::vec3 rd, myMisc::vec3 p, float w) {
  return -(myMisc::dot(ro, p) + w) / myMisc ::dot(rd, p);
}
