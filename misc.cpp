#include "misc.h"
#include <math.h>

myMisc::vec2 myMisc::sphere(myMisc::vec3 camPos, myMisc::vec3 dirRay, float r) {
  float b = myMisc::dot(camPos, dirRay);
  float c = myMisc::dot(camPos, camPos) - r * r;
  float h = b * b - c;
  if (h < 0.0)
    return myMisc::vec2(-1.0);
  h = sqrt(h);
  return myMisc::vec2(-b - h, -b + h);
}
