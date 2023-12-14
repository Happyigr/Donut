#include "misc.h"
#include "terminal.h"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iterator>
#include <string>
#include <thread>

int main(int argc, char **argv) {
  myMisc::Terminal term;
  float pixelAspect = 11.0f / 24.0f;
  std::string gradient = " .,;-=+*#%@";
  int gradientSize = std::size(gradient) - 2;

  char *screen = new char[term.m_width * term.m_heigth];

  for (int frame = 0; frame < 10000; frame++) {
    for (int i = 0; i < term.m_width; i++) {
      for (int j = 0; j < term.m_heigth; j++) {
        // the vector of the coords from center, which are from -1 to 1
        myMisc::vec2 uv = myMisc::vec2(i, j) /
                              myMisc::vec2(term.m_width, term.m_heigth) * 2.0f -
                          1.0f;

        // fixing the relationship with width and heigth so, that the x-border
        // of screen will be a little bit wider (when we haven't made this, then
        // our picture will be thinking, that our screen is a square, but not a
        // rectangle)
        uv.x *= term.m_aspect * pixelAspect;
        // animation
        uv.x += sin(frame * 0.001);

        // distance from center (|x|+|y|)^2
        float dist = sqrt(uv.x * uv.x + uv.y * uv.y);
        int color = (int)(dist * 3);

        color = myMisc::clamp(color, 0, gradientSize);

        screen[i + j * term.m_width] = gradient[color];
      }
    }
    term.ShowContent(screen);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  getchar();

  return 0; // make sure your main returns int
}
