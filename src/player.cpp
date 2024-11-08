#include "player.hpp"
#include "cell.hpp"
#include "raylib.h"

Player::Player(std::string name) : mName(name), Board(0, 0)
{
    InitShips();
}

void Player::InitShips()
{

    int x = Global::windowWidth - 500;
    int y = 150;

    for (int i = 0; i < 4; i++)
    {
        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_1});

        x += 100;
    }
    x = Global::windowWidth - 500;
    y = 225; // boat 1 by 2, 3 pieces only: ##
    for (int i = 0; i < 3; i++)
    {
        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_2});

        x += 100 + (Global::sizeOfTile - 1);
    }
    x = Global::windowWidth - 500;
    y = 300;
    // boat 1 by 3, 2 pieces only: ###
    for (int i = 0; i < 2; i++)
    {

        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_3});

        x += 100 + (Global::sizeOfTile - 1) * 2;
    }
    x = Global::windowWidth - 500;
    y = 375;

    // boat 1 by 4, 1 pieces only: ####
    for (int i = 0; i < 1; i++)
    {
        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_4});

        x += 100 + (Global::sizeOfTile - 1) * 3;
    }
}

void Player::Draw(int offsetX, int offsetY, bool hide = 0)
{
    mOffset.x = offsetX;
    mOffset.y = offsetY;
    int rotate = mShips[mCurrShipId].rotate;
    Board::Draw(hide);

    using namespace Global; // for sizeOfTile

    if (mCurrShipId != -1)
        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
            {
                if (CheckCellCollision(GetMousePosition(), Vector2{x, y}))
                {
                    switch (mShips[mCurrShipId].mCellState)
                    {
                    case CellState::SHIP_1:
                        if (!IsAreaEmpty(x - 1, y - 1, 3, 3))
                            DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x, y * sizeOfTile + 1 + mOffset.y,
                                     RED);
                        else
                            DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x, y * sizeOfTile + 1 + mOffset.y,
                                     GREEN);
                        break;

                    case CellState::SHIP_2:
                        if (!rotate)
                        {
                            if (x < 9)
                                if (!IsAreaEmpty(x - 1, y - 1, 4, 3))
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, RED);
                                else
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, GREEN);
                        }
                        else
                        {
                            if (y < 9)
                                if (!IsAreaEmpty(x - 1, y - 1, 3, 4))
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, RED);
                                else
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, GREEN);
                        }
                        break;

                    case CellState::SHIP_3:
                        if (!rotate)
                        {
                            if (x < 8)

                                if (!IsAreaEmpty(x - 1, y - 1, 5, 3))
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, RED);
                                else
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, GREEN);
                        }
                        else
                        {
                            if (y < 8)

                                if (!IsAreaEmpty(x - 1, y - 1, 3, 5))
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, RED);
                                else
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, GREEN);
                        }
                        break;

                    case CellState::SHIP_4:
                        if (!rotate)
                        {
                            if (x < 7)
                                if (!IsAreaEmpty(x - 1, y - 1, 6, 3))
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, RED);
                                else
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, GREEN);
                        }
                        else
                        {
                            if (y < 7)
                                if (!IsAreaEmpty(x - 1, y - 1, 3, 6))
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, RED);
                                else
                                    DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                             y * sizeOfTile + 1 + mOffset.y, GREEN);
                        }
                        break;
                    }
                }
            }

    for (int i = 0; i < mShips.size(); i++)
    {
        Vector2 &pos = mShips[i].mPos;
        CellState &type = mShips[i].mCellState;
        DrawShip(mShips[i], pos, WHITE);
    }
}

bool Player::HandleShipPlacement(int x, int y)
{
    bool result = 1;

    bool rotate = mShips[mCurrShipId].rotate;

    switch (mShips[mCurrShipId].mCellState)
    {
    case CellState::SHIP_1:
        if (IsAreaEmpty(x - 1, y - 1, 3, 3))
        {
            PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
            mShips.erase(mShips.begin() + mCurrShipId);
            mCurrShipId = -1;
        }
        break;

    case CellState::SHIP_2:
        if (!rotate)
        {
            if (x < 9)
            {
                if (IsAreaEmpty(x - 1, y - 1, 4, 3))
                {
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
            }
        }
        else
        {
            if (y < 9)
            {
                if (IsAreaEmpty(x - 1, y - 1, 3, 4))
                {
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y + 1});
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
            }
        }
        break;

    case CellState::SHIP_3:
        if (!rotate)
        {
            if (x < 8)
            {
                if (IsAreaEmpty(x - 1, y - 1, 5, 3))
                {
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2, y});
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
            }
        }
        else
        {
            if (y < 8)
                if (IsAreaEmpty(x - 1, y - 1, 3, 5))
                {
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y + 1});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y + 2});
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
        }
        break;

    case CellState::SHIP_4:
        if (!rotate)
        {
            if (x < 7)
            {
                if (IsAreaEmpty(x - 1, y - 1, 6, 3))
                {
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 3, y});
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
            }
        }
        else
        {
            if (y < 7)
            {
                if (IsAreaEmpty(x - 1, y - 1, 3, 6))
                {
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y + 1});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y + 2});
                    PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y + 3});
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
            }
        }
        break;
    }

    return result;
}

void Player::UpdateCurrShip()
{
    if (mCurrShipId != -1)
    {
        if (IsKeyPressed(KEY_R))
            mShips[mCurrShipId].rotate = !mShips[mCurrShipId].rotate;

        Vector2 mousePos = GetMousePosition();

        Vector2 &shipPos = mShips[mCurrShipId].mPos;
        mousePos.x -= 22;
        mousePos.y -= 22;

        shipPos = GetSplinePointLinear(mousePos, shipPos, 0.7f);
    }
}

void Player::HandleShipSelection()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < mShips.size(); i++)
        {
            Vector2 pos = mShips[i].mPos;
            CellState type = mShips[i].mCellState;
            bool rotate = mShips[i].rotate;

            switch (type)
            {
            case CellState::SHIP_1:
                if (CheckCollisionPointRec(GetMousePosition(),
                                           Rectangle{pos.x, pos.y, (Global::sizeOfTile - 1), (Global::sizeOfTile - 1)}))
                    mCurrShipId = i;
                break;

            case CellState::SHIP_2:
                if (!rotate)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile * 2 - 1),
                                                                             (Global::sizeOfTile - 1)}))
                        mCurrShipId = i;
                }
                else
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile - 1),
                                                                             (Global::sizeOfTile * 2 - 1)}))
                        mCurrShipId = i;
                }
                break;

            case CellState::SHIP_3:
                if (!rotate)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile * 3 - 1),
                                                                             (Global::sizeOfTile - 1)}))
                        mCurrShipId = i;
                }
                else
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile - 1),
                                                                             (Global::sizeOfTile * 3 - 1)}))
                        mCurrShipId = i;
                }
                break;

            case CellState::SHIP_4:
                if (!rotate)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile * 4 - 1),
                                                                             (Global::sizeOfTile - 1)}))
                        mCurrShipId = i;
                }
                else
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile - 1),
                                                                             (Global::sizeOfTile * 4 - 1)}))
                        mCurrShipId = i;
                }
                break;
            }
        }
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        mCurrShipId = -1;
    }
}
