#pragma once
#include "cell.hpp"
#include <iostream>
#include <raylib.h>

class Button
{
  public:
    Button(Rectangle rect);
    bool IsButtonPressed(int MouseButton);
    bool IsMouseOverButton();
    void Draw(Color color);

  private:
    Rectangle mRect;
};
