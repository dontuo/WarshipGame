#pragma once
#include "cell.h"
#include <raylib.h>
#include <vector>
#include <iostream>

extern Texture2D textures[];

void DrawShip(CellState type, int offsetX, int offsetY, Color color);
void DrawShip(CellState type, Vector2 offset, Color color);

void LoadTextures();


struct Ship
{
    Vector2 mPos;
    CellState mCellState;
    bool rotate = 0;
    //if rotate == 1 then rotate ship by 90 degree
};
