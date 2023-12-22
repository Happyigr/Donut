#include "Terminal.h"
#include <unistd.h>

myMisc::Terminal::Terminal(float pixelAspect) {
  initscr();                           /* start the curses mode */
  cbreak();                            // Disable line buffering
  noecho();                            // Don't echo input
  getmaxyx(stdscr, m_heigth, m_width); /* get the number of rows and columns */

  m_aspect = float(m_width) / m_heigth * pixelAspect;
  m_colors = " .:!/r(l1Z4H9W8$@";
}

myMisc::Terminal::~Terminal() { endwin(); }

void myMisc::Terminal::ShowContent(wchar_t *frame) {
  mvwprintw(stdscr, 0, 0, "%ls", frame);
  refresh();
  usleep(10000);
}
