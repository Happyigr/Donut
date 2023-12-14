#include "Terminal.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

Terminal::Terminal() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  m_rows = w.ws_row;
  m_lines = w.ws_col;
}

void Terminal::GetInfo() {
  std::cout << "Rows: " << m_rows << "\nLines: " << m_lines << std::endl;
}
