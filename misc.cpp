#include "misc.h"
#include <math.h>

float myMisc::clamp(float value, float min, float max) {
  return fmax(fmin(value, max), min);
}
