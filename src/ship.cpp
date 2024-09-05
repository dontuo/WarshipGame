#include "ship.h"

void LoadTextures()
{
    textures[CellState::EMPTY] = LoadTexture("textures/empty.png"); 
    textures[CellState::BOAT_1] = LoadTexture("textures/ship_1.png"); 
    textures[CellState::BOAT_2] = LoadTexture("textures/ship_2.png"); 
    textures[CellState::BOAT_3] = LoadTexture("textures/ship_3.png"); 
    textures[CellState::BOAT_4] = LoadTexture("textures/ship_4.png"); 
    textures[CellState::BOAT_1_HITTED] = LoadTexture("textures/ship_1_hitted.png"); 
    textures[CellState::BOAT_2_HITTED] = LoadTexture("textures/ship_2_hitted.png"); 
    textures[CellState::BOAT_3_HITTED] = LoadTexture("textures/ship_3_hitted.png"); 
    textures[CellState::BOAT_4_HITTED] = LoadTexture("textures/ship_4_hitted.png"); 
    textures[CellState::HIT] = LoadTexture("textures/hit.png"); 
    textures[CellState::MISSED] = LoadTexture("textures/miss.png");
}

void DrawShip(CellState type, int offsetX, int offsetY, Color color)
{
    switch (type)
    {
        case CellState::BOAT_1:
            DrawTexture(textures[CellState::BOAT_1], offsetX, offsetY, color);
        break;
        
        case CellState::BOAT_2:
            DrawTexture(textures[CellState::BOAT_2], offsetX,offsetY, color);
            DrawTexture(textures[CellState::BOAT_2], offsetX + 44, offsetY, color);
        break;

        case CellState::BOAT_3:
            DrawTexture(textures[CellState::BOAT_3], offsetX, offsetY, color);
            DrawTexture(textures[CellState::BOAT_3], offsetX + 44, offsetY, color);
            DrawTexture(textures[CellState::BOAT_3], offsetX + 44 * 2, offsetY, color);
        break;

        case CellState::BOAT_4:
            DrawTexture(textures[CellState::BOAT_4], offsetX, offsetY, color);
            DrawTexture(textures[CellState::BOAT_4], offsetX + 44, offsetY, color);
            DrawTexture(textures[CellState::BOAT_4], offsetX + 44 * 2, offsetY, color);
            DrawTexture(textures[CellState::BOAT_4], offsetX + 44 * 3, offsetY, color);
        break;
    } 
}
