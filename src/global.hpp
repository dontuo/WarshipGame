#pragma once
#include <raylib.h>
namespace Global
{
static int windowWidth = 1280;
static int windowHeight = 720;

// size of 1 tile (literally size of texture)
constexpr int sizeOfTile = 45;
// offset for drawing grid
static int offsetX = 100;
static int offsetY = 150;

static Color backgroundColor{36, 33, 68, 255};
} // namespace Global
