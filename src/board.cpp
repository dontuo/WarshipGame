#include "board.hpp"

Board::Board(int offsetX, int offsetY) : mOffset{(float)offsetX, (float)offsetY}
{
}

Board::Board(Vector2 offset) : mOffset(offset)
{
}

void Board::Draw(bool Hide)
{
    DrawGrid(10, 10, Global::sizeOfTile, mOffset.x, mOffset.y + 1, BLACK);

    if (Hide)
    {
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                switch (mCells[x][y])
                {

                case CellState::EMPTY:
                    DrawTexture(textures[CellState::EMPTY], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_1_HITTED:
                    DrawTexture(textures[CellState::SHIP_1_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_2_HITTED:
                    DrawTexture(textures[CellState::SHIP_2_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_3_HITTED:
                    DrawTexture(textures[CellState::SHIP_3_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_4_HITTED:
                    DrawTexture(textures[CellState::SHIP_4_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::MISSED:
                    DrawTexture(textures[CellState::MISSED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::HIT:
                    DrawTexture(textures[CellState::HIT], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                default:
                    DrawTexture(textures[CellState::EMPTY], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;
                }
            }
        }
    }
    else
    {
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                switch (mCells[x][y])
                {
                case CellState::EMPTY:
                    DrawTexture(textures[CellState::EMPTY], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_1:
                    DrawTexture(textures[CellState::SHIP_1], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_2:
                    DrawTexture(textures[CellState::SHIP_2], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_3:
                    DrawTexture(textures[CellState::SHIP_3], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_4:
                    DrawTexture(textures[CellState::SHIP_4], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_1_HITTED:
                    DrawTexture(textures[CellState::SHIP_1_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_2_HITTED:
                    DrawTexture(textures[CellState::SHIP_2_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_3_HITTED:
                    DrawTexture(textures[CellState::SHIP_3_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::SHIP_4_HITTED:
                    DrawTexture(textures[CellState::SHIP_4_HITTED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::MISSED:
                    DrawTexture(textures[CellState::MISSED], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                case CellState::HIT:
                    DrawTexture(textures[CellState::HIT], mOffset.x + (Global::sizeOfTile * x),
                                mOffset.y + (Global::sizeOfTile * y) + 1, WHITE);
                    break;

                default:
                    DrawRectangle(mOffset.x + (Global::sizeOfTile * x), mOffset.y + (Global::sizeOfTile * y) + 1,
                                  (Global::sizeOfTile - 1), (Global::sizeOfTile - 1), WHITE);
                    break;
                }
            }
        }
    }
}

bool Board::PlaceShip(CellState type, Vector2 position)
{
    bool result = 1;

    mCells[(int)position.x][(int)position.y] = type;

    return result;
}

bool CheckHit()
{
    // yeah... In the future
    bool result = 0;

    return result;
}

bool Board::CheckCellCollision(Vector2 pos, Vector2 cell)
{
    return (CheckCollisionPointRec(pos, Rectangle{cell.x * Global::sizeOfTile + mOffset.x,
                                                  cell.y * Global::sizeOfTile + mOffset.y, (Global::sizeOfTile - 1),
                                                  (Global::sizeOfTile - 1)}));
}

CellState Board::GetCellState(int x, int y)
{
    return mCells[x][y];
}

CellState Board::GetCellState(Vector2 pos)
{
    return mCells[static_cast<int>(pos.x)][static_cast<int>(pos.y)];
}

bool Board::IsAreaEmpty(int x, int y, int width, int height)
{
    // checking borders
    while (y < 0 or x < 0 or x + width > 10 or y + height > 10)
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
            continue;

        if (x + width > 10)
        {
            width--;
        }
        if (y + height > 10)
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
