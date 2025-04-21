#pragma once
#include "cell.hpp"
#include "global.hpp"
#include "grid.hpp"
#include "ship.hpp"
#include <iostream>
#include <raylib.h>
#include <vector>

constexpr int BOARD_SIZE = 10;

Rectangle ClampRectangleToBounds(int x, int y, int width, int height);

class Board
{
  public:
    Board(int offsetX, int offsetY);
    Board(Vector2 offset);

    void Draw(bool Hide = 0);

    CellState GetCellState(int x, int y);
    CellState GetCellState(Vector2 pos);

    void SetCellState(int x, int y, CellState state);
    void SetCellState(Vector2 pos, CellState state);

    Vector2 GetOffset();
    void SetOffset(Vector2 offset);
    void SetOffset(float offsetX, float offsetY);

    bool IsAreaEmpty(int x, int y, int width, int height);
    bool CheckCellCollision(Vector2 pos, Vector2 cell);

    void markSurroundings(const std::vector<Vector2>& shipCoord);
    bool IsInBounds(int x, int y);

    void processHits();

private:
    CellState mCells[10][10] = {CellState::EMPTY};
    Vector2 mOffset;
};
