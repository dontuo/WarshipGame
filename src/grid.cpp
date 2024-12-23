#include "grid.hpp"

Grid::Grid(int row, int column, int size, int offsetX, int offsetY) : mRow(row), mColumn(column), mSize(size), mOffsetX(offsetX), mOffsetY(offsetY)
{
}

void DrawGrid(int row, int column, int size, int offsetX, int offsetY, Color color)
{
    for (int x = 0; x <= row; x++)
        DrawLine(x * size + offsetX, offsetY, x * size + offsetX, column * size + offsetY, color);

    for (int y = 0; y <= column; y++)
        DrawLine(offsetX - 1, y * size + offsetY, row * size + offsetX, y * size + offsetY, color);
}

void Grid::Draw()
{
    for (int x = 0; x <= mRow; x++)
        DrawLine(x * mSize + mOffsetX, mOffsetY, x * mSize + mOffsetX, mColumn * mSize + mOffsetY, WHITE);

    for (int y = 0; y <= mColumn; y++)
        DrawLine(mOffsetX - 1, y * mSize + mOffsetY, mRow * mSize + mOffsetX, y * mSize + mOffsetY, WHITE);
}

void Grid::SetOffset(int offsetX, int offsetY)
{
    mOffsetX = offsetX;
    mOffsetY = offsetY;
}
void Grid::SetRowColumn(int row, int column)
{
    mRow = row;
    mColumn = column;
}
void Grid::SetSize(int size)
{
    mSize = size;
}
