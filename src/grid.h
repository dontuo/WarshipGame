#pragma once
#include <raylib.h>
class Grid
{
public:
    void Draw();
    Grid(int row, int column, int size, int offsetX, int offsetY, Color color);
private:
    int mRow;
    int mColumn;
    int mSize;
    int mOffsetX;
    int mOffsetY;
    Color mColor;
};
void DrawGrid(int row, int column, int size, int offsetX, int offsetY, Color color);
