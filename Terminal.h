#pragma once
#include <ncurses.h>
#include <string>
namespace myMisc {

class Terminal {
public:
  Terminal(float pixelAspect);
  ~Terminal();
  int m_width;
  int m_heigth;
  float m_aspect;
  // colors that we have from the darkest, to the lightest
  std::string m_colors;
  void ShowContent(wchar_t *frame);
};
} // namespace myMisc
