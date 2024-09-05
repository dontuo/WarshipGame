#pragma once
#include <raylib.h>
#include <iostream>

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
