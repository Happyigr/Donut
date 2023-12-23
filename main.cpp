#include "Sphere.h"
#include "Terminal.h"
#include <ncurses.h>
#include <string>

int main(int argc, char **argv) {
  // terminal initialization with pixel aspect(11px wide and 24px high)
  myMisc::Terminal term(11.0f / 24.0f);

  std::string gradient = term.m_colors;
  int gradientSize = term.m_colors.size() - 1;

  wchar_t *screen = new wchar_t[term.m_width * term.m_heigth + 1];
  screen[term.m_width * term.m_heigth] = '\0';

  for (int frame = 0; frame < 10000; frame++) {
    myMisc::vec3 light = myMisc::norm(myMisc::vec3(0, 0, -1));
    // we full up the screen from up to down, from left to right
    for (int i = 0; i < term.m_width; i++) {
      for (int j = 0; j < term.m_heigth; j++) {
        // distance from the center of the screen to the pixel
        myMisc::vec2 uv = myMisc::vec2(i, j) /
                              myMisc::vec2(term.m_width, term.m_heigth) * 2.0f -
                          1.0f;

        uv.x *= term.m_aspect;

        myMisc::vec3 camPos = myMisc::vec3(0, 0, -3);
        myMisc::vec3 cameraRay = myMisc::norm(myMisc::vec3(uv, 1));

        myMisc::vec2 intersection = myMisc::sphere(camPos, cameraRay, 2);

        int color = 0;
        if (intersection.x > 0) {
          myMisc::vec3 itPoint = camPos + cameraRay * intersection.x;

          // max brigtness on angle 0, min on angle 90(pi/2 in radians);
          float angle = myMisc::dot(myMisc::norm(itPoint), light);
          color = (int)(angle * 10);
        }

        color = myMisc::clamp(color, 0, gradientSize);
        screen[i + j * term.m_width] = gradient[color];
      }
    }
    term.ShowContent(screen);
  }
  getch();
}
