#include "terminal.h"
#include <sys/ioctl.h>
#include <unistd.h>

myMisc::Terminal::Terminal() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  m_heigth = w.ws_row;
  m_width = w.ws_col;
  m_aspect = float(m_width) / m_heigth;
}

void myMisc::Terminal::ShowContent(char *frame) {
  for (int j = 0; j < m_heigth; j++) {
    for (int i = 0; i < m_width; i++) {
      std::cout << frame[i + j * m_width];
    }
    std::cout << std::endl;
  }
}
