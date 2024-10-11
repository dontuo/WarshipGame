#include "ship.hpp"

Texture2D textures[CellState::ELEMENT_COUNT] = {};

void LoadTextures()
{
    textures[CellState::EMPTY] = LoadTexture("textures/empty.png");
    textures[CellState::SHIP_1] = LoadTexture("textures/ship_1.png");
    textures[CellState::SHIP_2] = LoadTexture("textures/ship_2.png");
    textures[CellState::SHIP_3] = LoadTexture("textures/ship_3.png");
    textures[CellState::SHIP_4] = LoadTexture("textures/ship_4.png");
    textures[CellState::SHIP_1_HITTED] = LoadTexture("textures/ship_1_hitted.png");
    textures[CellState::SHIP_2_HITTED] = LoadTexture("textures/ship_2_hitted.png");
    textures[CellState::SHIP_3_HITTED] = LoadTexture("textures/ship_3_hitted.png");
    textures[CellState::SHIP_4_HITTED] = LoadTexture("textures/ship_4_hitted.png");
    textures[CellState::HIT] = LoadTexture("textures/hit.png");
    textures[CellState::MISSED] = LoadTexture("textures/miss.png");
}

void DrawShip(CellState type, int offsetX, int offsetY, Color color)
{
    // TODO: maybe make it with for loop?
    switch (type)
    {
        case CellState::SHIP_1:
            DrawTexture(textures[CellState::SHIP_1], offsetX, offsetY, color);
            break;

        case CellState::SHIP_2:
            DrawTexture(textures[CellState::SHIP_2], offsetX, offsetY, color);
            DrawTexture(textures[CellState::SHIP_2], offsetX + (Global::sizeOfTile - 1), offsetY, color);
            break;

        case CellState::SHIP_3:
            DrawTexture(textures[CellState::SHIP_3], offsetX, offsetY, color);
            DrawTexture(textures[CellState::SHIP_3], offsetX + (Global::sizeOfTile - 1), offsetY, color);
            DrawTexture(textures[CellState::SHIP_3], offsetX + (Global::sizeOfTile - 1) * 2, offsetY, color);
            break;

        case CellState::SHIP_4:
            DrawTexture(textures[CellState::SHIP_4], offsetX, offsetY, color);
            DrawTexture(textures[CellState::SHIP_4], offsetX + (Global::sizeOfTile - 1), offsetY, color);
            DrawTexture(textures[CellState::SHIP_4], offsetX + (Global::sizeOfTile - 1) * 2, offsetY, color);
            DrawTexture(textures[CellState::SHIP_4], offsetX + (Global::sizeOfTile - 1) * 3, offsetY, color);
            break;
    }
}

void DrawShip(CellState type, Vector2 offset, Color color)
{
    switch (type)
    {
        case CellState::SHIP_1:
            DrawTexture(textures[CellState::SHIP_1], offset.x, offset.y, color);
            break;

        case CellState::SHIP_2:
            DrawTexture(textures[CellState::SHIP_2], offset.x, offset.y, color);
            DrawTexture(textures[CellState::SHIP_2], offset.x + (Global::sizeOfTile - 1), offset.y, color);
            break;

        case CellState::SHIP_3:
            DrawTexture(textures[CellState::SHIP_3], offset.x, offset.y, color);
            DrawTexture(textures[CellState::SHIP_3], offset.x + (Global::sizeOfTile - 1), offset.y, color);
            DrawTexture(textures[CellState::SHIP_3], offset.x + (Global::sizeOfTile - 1) * 2, offset.y, color);
            break;

        case CellState::SHIP_4:
            DrawTexture(textures[CellState::SHIP_4], offset.x, offset.y, color);
            DrawTexture(textures[CellState::SHIP_4], offset.x + (Global::sizeOfTile - 1), offset.y, color);
            DrawTexture(textures[CellState::SHIP_4], offset.x + (Global::sizeOfTile - 1) * 2, offset.y, color);
            DrawTexture(textures[CellState::SHIP_4], offset.x + (Global::sizeOfTile - 1) * 3, offset.y, color);
            break;
    }
}
