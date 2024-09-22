#include "button.hpp"

Button::Button(Rectangle rect) : mRect(rect)
{
}

bool Button::IsButtonPressed(int MouseButton)
{
    return CheckCollisionPointRec(GetMousePosition(), mRect) && IsMouseButtonPressed(MouseButton);
}

void Button::Draw(Color color)
{
    DrawRectangleRec(mRect, color);
}

bool Button::IsMouseOverButton()
{
    return CheckCollisionPointRec(GetMousePosition(), mRect);
}
