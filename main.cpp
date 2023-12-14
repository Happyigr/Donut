#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>

int main(int argc, char **argv) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  int heigth = w.ws_row;
  int width = w.ws_col;
  float aspect = float(width) / heigth;
  float pixelAspect = 11.0f / 24.0f;
  char gradient[] = " .,;-=+*#%@";
  int gradientSize = std::size(gradient) - 2;

  float circleRadius = 0.5;
  float gradientWide = 0.2;

  char *screen = new char[width * heigth];

  /* for (int frame = 0; frame < 10; frame++) { */
  for (int frame = 0; frame < 10000; frame++) {
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < heigth; j++) {
        // make our screen to be from -1.0 to 1.0 in x and y coordinates
        float x = (float(i) / width) * 2.0f - 1.0f;
        float y = (float(j) / heigth) * 2.0f - 1.0f;
        // make the center of the sym in screen to be in a center of a sym
        x *= aspect * pixelAspect;
        // animation
        x += sin(frame * 0.001);

        // distance from center (|x|+|y|)^2
        float dist = sqrt(x * x + y * y);
        int brightness = (int)(1 / dist * 8) - 2;

        if (brightness > gradientSize)
          brightness = gradientSize;
        if (brightness < 0) {
          brightness = 0;
        }

        screen[i + j * width] = gradient[brightness];
      }
    }
    for (int j = 0; j < heigth; j++) {
      for (int i = 0; i < width; i++) {
        std::cout << screen[i + j * width];
      }
      std::cout << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  getchar();

  return 0; // make sure your main returns int
}
