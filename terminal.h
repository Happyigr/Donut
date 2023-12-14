#pragma once
#include <iostream>

namespace myMisc {

class Terminal {
public:
  Terminal();
  int m_width;
  int m_heigth;
  float m_aspect;
  void ShowContent(char[]);
};
} // namespace myMisc
