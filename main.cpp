#include "misc.h"
#include "terminal.h"
#include "vec2.h"
#include "vec3.h"
#include <chrono>
#include <cstdio>
#include <iterator>
#include <string>
#include <thread>

int main(int argc, char **argv) {
  myMisc::Terminal term;
  float pixelAspect = 11.0f / 24.0f;
  std::string gradient = " .:!/r(l1Z4H9W8$@";
  int gradientSize = std::size(gradient) - 2;

  char *screen = new char[term.m_width * term.m_heigth];

  for (int frame = 0; frame < 10000; frame++) {
    myMisc::vec3 light = myMisc::norm(
        myMisc::vec3(sin(frame * 0.001), sin(0.01), sin(0.001 * frame)));
    for (int i = 0; i < term.m_width; i++) {
      for (int j = 0; j < term.m_heigth; j++) {
        // coords of the pixel on monitor form 0 to 1
        myMisc::vec2 uv = myMisc::vec2(i, j) /
                              myMisc::vec2(term.m_width, term.m_heigth) * 2.0f -
                          1.0f;

        // fixing the relationship with width and heigth so, that the
        // x-border of screen will be a little bit wider (when we haven't
        // made this, then our picture will be thinking, that our screen is
        // a square, but not a rectangle)
        uv.x *= term.m_aspect * pixelAspect;

        // camera position
        myMisc::vec3 camPos = myMisc::vec3(0, 0, -5);
        // the ray from camera to pixel, that has coords x=i y=j
        myMisc::vec3 rd = myMisc::norm(myMisc::vec3(uv, 1));

        // animation
        // 3d sphere

        myMisc::vec2 intersection = myMisc::sphere(camPos, rd, 2);

        int color = 0;
        char pixel = ' ';
        if (intersection.x > 0) {
          myMisc::vec3 itPoint = camPos + rd * intersection.x;
          myMisc::vec3 n = myMisc::norm(itPoint);
          float diff = myMisc::dot(n, light);
          color = (int)(diff * 20);
        }
        color = myMisc::clamp(color, 0, gradientSize);
        pixel = gradient[color];
        screen[i + j * term.m_width] = gradient[color];
      }
    }
    term.ShowContent(screen);

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  getchar();

  return 0; // make sure your main returns int
}
