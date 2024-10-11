#pragma once
#include "cell.hpp"
#include "global.hpp"
#include <vector>
#include <iostream>
#include <raymath.h>
#include <raylib.h>

extern Texture2D textures[];

void DrawShip(CellState type, int offsetX, int offsetY, Color color);
void DrawShip(CellState type, Vector2 offset, Color color);

void LoadTextures();

struct Ship
{
    Vector2 mPos;
    CellState mCellState;
    bool rotate = 0;
    // if rotate == 1 then rotate ship by 90 degree
};
