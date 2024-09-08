#pragma once
#include "cell.h"
#include <raylib.h>
#include <vector>
#include <iostream>

extern Texture2D textures[];
void DrawShip(CellState type, int offsetX, int offsetY, Color color);

void LoadTextures();


struct Ship
{
    Vector2 mPos;
    CellState mCellState;
};
