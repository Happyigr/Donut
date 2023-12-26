#include "Misc.h"
#include "Terminal.h"
#include <ncurses.h>
#include <string>

using namespace myMisc;
int main(int argc, char **argv) {
  // terminal initialization with pixel aspect(11px wide and 24px high)
  myMisc::Terminal term(11.0f / 24.0f);

  std::string gradient = term.m_colors;
  int gradientSize = term.m_colors.size() - 2;

  wchar_t *screen = new wchar_t[term.m_width * term.m_heigth];
  for (int t = 0;; t++) {
    vec3 light = norm(vec3(-0.5, 0.5, -1.0));
    vec3 spherePos = vec3(0, 3, 0);
    for (int i = 0; i < term.m_width; i++) {
      for (int j = 0; j < term.m_heigth; j++) {
        vec2 uv = vec2(i, j) / vec2(term.m_width, term.m_heigth) * 2.0f - 1.0f;
        uv.x *= term.m_aspect;
        vec3 ro = vec3(-6, 0, 0);
        vec3 rd = norm(vec3(2, uv));
        ro = rotateY(ro, 0.25);
        rd = rotateY(rd, 0.25);
        ro = rotateZ(ro, t * 0.01);
        rd = rotateZ(rd, t * 0.01);
        float diff = 1;
        for (int k = 0; k < 5; k++) {
          float minIt = 99999;
          vec2 intersection = sphere(ro - spherePos, rd, 1);
          vec3 n = 0;
          float albedo = 1;
          if (intersection.x > 0) {
            vec3 itPoint = ro - spherePos + rd * intersection.x;
            minIt = intersection.x;
            n = norm(itPoint);
          }
          vec3 boxN = 0;
          intersection = box(ro, rd, 1, boxN);
          if (intersection.x > 0 && intersection.x < minIt) {
            minIt = intersection.x;
            n = boxN;
          }
          intersection = plane(ro, rd, vec3(0, 0, -1), 1);
          if (intersection.x > 0 && intersection.x < minIt) {
            minIt = intersection.x;
            n = vec3(0, 0, -1);
            albedo = 0.5;
          }
          if (minIt < 99999) {
            diff *= (dot(n, light) * 0.5 + 0.5) * albedo;
            ro = ro + rd * (minIt - 0.01);
            rd = reflect(rd, n);
          } else
            break;
        }
        int color = (int)(diff * 20);
        color = clamp(color, 0, gradientSize);
        char pixel = gradient[color];
        screen[i + j * term.m_width] = pixel;
      }
    }
    term.ShowContent(screen);
  }
  getch();
}
