#include "board.hpp"
#include "cell.hpp"
#include "raylib.h"
#include <cassert>
#include <iostream>
#include <string>

Board::Board(int offsetX, int offsetY) : mOffset{(float)offsetX, (float)offsetY}
{
}

Board::Board(Vector2 offset) : mOffset(offset)
{
}

void Board::Draw(bool Hide)
{
    DrawGrid(BOARD_SIZE, BOARD_SIZE, Global::sizeOfTile, mOffset.x, mOffset.y + 1, BLACK);

    if (Hide)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                switch (mCells[x][y])
                {

                case CellState::EMPTY:
                    DrawTexture(textures[CellState::EMPTY], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_1_HITTED:
                    DrawTexture(textures[CellState::SHIP_1_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_2_HITTED:
                    DrawTexture(textures[CellState::SHIP_2_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_3_HITTED:
                    DrawTexture(textures[CellState::SHIP_3_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_4_HITTED:
                    DrawTexture(textures[CellState::SHIP_4_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::MISSED:
                    DrawTexture(textures[CellState::MISSED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::HIT:
                    DrawTexture(textures[CellState::HIT], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                default:
                    DrawTexture(textures[CellState::EMPTY], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;
                }
            }
        }
    }
    else
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                switch (mCells[x][y])
                {
                case CellState::EMPTY:
                    DrawTexture(textures[CellState::EMPTY], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_1:
                    DrawTexture(textures[CellState::SHIP_1], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_2:
                    DrawTexture(textures[CellState::SHIP_2], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_3:
                    DrawTexture(textures[CellState::SHIP_3], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_4:
                    DrawTexture(textures[CellState::SHIP_4], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_1_HITTED:
                    DrawTexture(textures[CellState::SHIP_1_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_2_HITTED:
                    DrawTexture(textures[CellState::SHIP_2_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_3_HITTED:
                    DrawTexture(textures[CellState::SHIP_3_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_4_HITTED:
                    DrawTexture(textures[CellState::SHIP_4_HITTED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::MISSED:
                    DrawTexture(textures[CellState::MISSED], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::HIT:
                    DrawTexture(textures[CellState::HIT], mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                default:
                    DrawRectangle(mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1, (Global::sizeOfTile - 1), (Global::sizeOfTile - 1), WHITE);
                    break;
                }
            }
        }
    }
}


bool CheckHit()
{
    // yeah... In the future
    bool result = 0;

    return result;
}

bool Board::CheckCellCollision(Vector2 pos, Vector2 cell)
{
    return (CheckCollisionPointRec(pos, Rectangle{cell.x * Global::sizeOfTile + mOffset.x, cell.y * Global::sizeOfTile + mOffset.y, (Global::sizeOfTile - 1), (Global::sizeOfTile - 1)}));
}

bool Board::IsAreaEmpty(int x, int y, int width, int height)
{
    // Clamp the area so it doesn't exceed the board limits
    while (y < 0 or x < 0 or x + width > BOARD_SIZE or y + height > BOARD_SIZE)
    {
        if (y < 0)
        {
            y++;
            height--;
        }
        if (x < 0)
        {
            x++;
            width--;
        }

        if (x < 0 || y < 0)
        {
            continue;
        }

        if (x + width > BOARD_SIZE)
        {
            width--;
        }
        if (y + height > BOARD_SIZE)
        {
            height--;
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (GetCellState(x + i, y + j) != CellState::EMPTY)
                return false;
        }
    }
    return true;
}

Rectangle ClampRectangleToBounds(int x, int y, int width, int height)
{
    while (y < 0 or x < 0 or x + width > BOARD_SIZE or y + height > BOARD_SIZE)
    {
        if (y < 0)
        {
            y++;
            height--;
        }
        if (x < 0)
        {
            x++;
            width--;
        }

        if (x < 0 || y < 0)
        {
            continue;
        }

        if (x + width > BOARD_SIZE)
        {
            width--;
        }
        if (y + height > BOARD_SIZE)
        {
            height--;
        }
    }

    return Rectangle{x, y, width, height};
}

CellState Board::GetCellState(int x, int y)
{
    assert(!(x >= BOARD_SIZE or x < 0 or y>= BOARD_SIZE or y < 0));
    return mCells[x][y];
}

CellState Board::GetCellState(Vector2 pos)
{
    assert(!(pos.x >= BOARD_SIZE or pos.x < 0 or pos.y>= BOARD_SIZE or pos.y < 0));
    return mCells[static_cast<int>(pos.x)][static_cast<int>(pos.y)];
}

void Board::SetCellState(int x, int y, CellState state)
{
    assert(!(x >= BOARD_SIZE or x < 0 or y>= BOARD_SIZE or y < 0));
    mCells[x][y] = state;
}
void Board::SetCellState(Vector2 pos, CellState state)
{
    assert(!(pos.x >= BOARD_SIZE or pos.x < 0 or pos.y>= BOARD_SIZE or pos.y < 0));
    mCells[static_cast<int>(pos.x)][static_cast<int>(pos.y)] = state;
}

Vector2 Board::GetOffset()
{
    return mOffset;
}

void Board::SetOffset(Vector2 offset)
{
    mOffset = offset;
}

void Board::SetOffset(float offsetX, float offsetY)
{
    mOffset.x = offsetX;
    mOffset.y = offsetY;
}

void Board::markSurroundings(const std::vector<Vector2>& shipCoord) {
    for (auto [x, y] : shipCoord) {
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++) {
                int nx = x + dx, ny = y + dy;
                if (IsInBounds(nx, ny) && mCells[nx][ny] == CellState::EMPTY)
                    mCells[nx][ny] = CellState::MISSED;
            }
    }
}

void Board::processHits()
{
    bool visited[BOARD_SIZE][BOARD_SIZE] = {};

    struct Coord{int x,y;};

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (mCells[i][j] == CellState::HIT && !visited[i][j]) {
                std::vector<Vector2> ship;

                // горизонталь
                int x = i, y = j;
                while (IsInBounds(x, y) && mCells[x][y] == CellState::HIT) {
                    visited[x][y] = true;
                    ship.push_back({x, y});
                    y++;
                }

                if (ship.size() == 1) { // можливо вертикаль
                    ship.clear();
                    x = i; y = j;
                    while (IsInBounds(x, y) && mCells[x][y] == CellState::HIT) {
                        visited[x][y] = true;
                        ship.push_back({x, y});
                        x++;
                    }
                }

                // перевірити, чи поряд немає непотоплених частин
                bool incomplete = false;
                for (auto [x, y] : ship) {
                    for (int dx = -1; dx <= 1; dx++)
                        for (int dy = -1; dy <= 1; dy++) {
                            int nx = x + dx, ny = y + dy;
                            if (IsInBounds(nx, ny)) {
                                CellState s = mCells[nx][ny];
                                if (s == CellState::SHIP_1 || s == CellState::SHIP_2 ||
                                    s == CellState::SHIP_3 || s == CellState::SHIP_4) {
                                    incomplete = true;
                                }
                            }
                        }
                }

                if (!incomplete) {
                    CellState hitType = CellState::SHIP_1_HITTED;
                    if (ship.size() == 2) hitType = CellState::SHIP_2_HITTED;
                    else if (ship.size() == 3) hitType = CellState::SHIP_3_HITTED;
                    else if (ship.size() == 4) hitType = CellState::SHIP_4_HITTED;

                    for (auto [x, y] : ship)
                        mCells[(int)x][(int)y] = hitType;

                    markSurroundings(ship);
                }
            }
        }
    }
}

bool Board::IsInBounds(int x, int y)
{
    return x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE;
}
