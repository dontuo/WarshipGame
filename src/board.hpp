#pragma once
#include "cell.hpp"
#include "global.hpp"
#include "grid.hpp"
#include "ship.hpp"
#include <iostream>
#include <raylib.h>
#include <vector>

Rectangle ClampRectangleToBounds(int x, int y, int width, int height);

class Board
{
  public:
    Board(int offsetX, int offsetY);
    Board(Vector2 offset);

    void Draw(bool Hide = 0);

    // void HightlighTheBoat(CellState type, Vector2 position);

    bool PlaceShip(CellState type, Vector2 position);
    int CountCellsInArea(Rectangle area, CellState type);
    CellState GetCellState(int x, int y);
    CellState GetCellState(Vector2 pos);

    bool IsAreaEmpty(int x, int y, int width, int height);
    bool CheckCellCollision(Vector2 pos, Vector2 cell);
    bool CheckHit(Vector2 pos);

    CellState mCells[10][10] = {CellState::EMPTY};
    Vector2 mOffset;
};
