#include "Misc.h"
#include "Terminal.h"
#include "Vec2.h"
#include <cmath>
#include <ncurses.h>
#include <string>

int main(int argc, char **argv) {
  // terminal initialization with pixel aspect(11px wide and 24px high)
  myMisc::Terminal term(11.0f / 24.0f);

  std::string gradient = term.m_colors;
  int gradientSize = term.m_colors.size() - 2;

  wchar_t *screen = new wchar_t[term.m_width * term.m_heigth + 1];
  screen[term.m_width * term.m_heigth] = '\0';

  // we full up the screen from up to down, from left to right
  for (int frame = 0; frame < 10000; frame++) {
    for (int i = 0; i < term.m_width; i++) {
      for (int j = 0; j < term.m_heigth; j++) {
        myMisc::vec2 uv = myMisc::vec2(i, j) /
                              myMisc::vec2(term.m_width, term.m_heigth) * 2.0f -
                          1.0f;

        uv.x *= term.m_aspect;

        uv.x += sin(frame * 0.01);

        int color = 0;
        if ((uv.x * uv.x + uv.y * uv.y) < 0.2) {
          color = 10;
        }

        color = myMisc::clamp(color, 0, gradientSize);
        screen[i + j * term.m_width] = gradient[color];
      }
    }
    term.ShowContent(screen);
  }
  getch();
}
