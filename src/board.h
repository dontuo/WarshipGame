#pragma once
#include <raylib.h>
#include "ship.h"
#include "cell.h"
#include "grid.h"
#include <iostream>

class Board
{
public:
    Board(int offsetX, int offsetY);
    Board(Vector2 offset);

    void Draw(bool Hide = 0);
    
    //void HightlighTheBoat(CellState type, Vector2 position);

    bool PlaceShip(CellState type, Vector2 position);
    
    bool CheckCollision(Vector2 pos, Vector2 cell);
    void PrintCells();
    bool CheckHit(Vector2 pos);
    
    CellState mCells[10][10] = {CellState::EMPTY};
    
    Vector2 mOffset;
    
    Texture2D mTextures[CellState::ELEMENT_COUNT];
};
