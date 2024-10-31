#pragma once
#include <raylib.h>

void DrawGrid(int row, int column, int size, int offsetX, int offsetY, Color color);

class Grid
{
  public:
    Grid(int row, int column, int size, int offsetX, int offsetY);

    void Draw();

    void SetOffset(int offsetX, int offsetY);
    void SetRowColumn(int row, int column);
    void SetSize(int size);

  private:
    int mRow;
    int mColumn;
    int mSize;
    int mOffsetX;
    int mOffsetY;
};
