#pragma once
#include "gamestate.hpp"
#include <raylib.h>

namespace Global
{
inline int windowWidth = 1280;
inline int windowHeight = 720;

// size of 1 tile (literally size of texture)
inline int sizeOfTile = 45;
// offset for drawing grid
inline int offsetX = 100;
inline int offsetY = 150;

inline Color backgroundColor{36, 33, 68, 255};
inline GameState gameState = GameState::GAME;

/*int row = 10;
int column = 10;
int size = 40;
static int offsetX = 100;
static int offsetY = 250;*/
} // namespace Global
