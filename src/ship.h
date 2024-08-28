#pragma once
#include "cell.h"
#include <raylib.h>
#include <vector>

static std::vector<Texture2D> textures(CellState::ELEMENT_COUNT);


void DrawShip(CellState type, int offsetX, int offsetY, Color color);

void LoadTextures();
