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
    Board::Draw(hide);

    using namespace Global; // for sizeOfTile

    if (mCurrShipId != -1)
    {
        int rotate = mShips[mCurrShipId].rotate;

        int sizeOfShip = 0;

        switch (mShips[mCurrShipId].mCellState)
        {
        case CellState::SHIP_1:
            sizeOfShip = 1;
            break;
        case CellState::SHIP_2:
            sizeOfShip = 2;
            break;
        case CellState::SHIP_3:
            sizeOfShip = 3;
            break;
        case CellState::SHIP_4:
            sizeOfShip = 4;
            break;
        }

        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
            {
                if (CheckCellCollision(GetMousePosition(), Vector2{x, y}))
                {
                    if (!rotate)
                    {
                        if (x < 11 - sizeOfShip)
                            if (!IsAreaEmpty(x - 1, y - 1, 2 + sizeOfShip, 3))
                            {
                                DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                         y * sizeOfTile + 1 + mOffset.y, RED);
                            }
                            else
                            {
                                DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                         y * sizeOfTile + 1 + mOffset.y, GREEN);
                            }
                    }
                    else
                    {
                        if (y < 11 - sizeOfShip)
                            if (!IsAreaEmpty(x - 1, y - 1, 3, 2 + sizeOfShip))
                                DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                         y * sizeOfTile + 1 + mOffset.y, RED);
                            else
                                DrawShip(mShips[mCurrShipId], x * sizeOfTile + mOffset.x,
                                         y * sizeOfTile + 1 + mOffset.y, GREEN);
                    }
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

void Player::HandleShipPlacement(int x, int y)
{
    if (mCurrShipId != -1)
    {
        bool rotate = mShips[mCurrShipId].rotate;

        int sizeOfShip = 0;

        switch (mShips[mCurrShipId].mCellState)
        {
        case CellState::SHIP_1:
            sizeOfShip = 1;
            break;
        case CellState::SHIP_2:
            sizeOfShip = 2;
            break;
        case CellState::SHIP_3:
            sizeOfShip = 3;
            break;
        case CellState::SHIP_4:
            sizeOfShip = 4;
            break;
        }

        if (!rotate)
        {
            if (x < 11 - sizeOfShip)
            {
                if (IsAreaEmpty(x - 1, y - 1, 2 + sizeOfShip, 3))
                {
                    for (int i = 0; i < sizeOfShip; i++)
                    {
                        PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + i, y});
                    }
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
            }
        }
        else
        {
            if (y < 11 - sizeOfShip)
            {
                if (IsAreaEmpty(x - 1, y - 1, 3, 2 + sizeOfShip))
                {
                    for (int i = 0; i < sizeOfShip; i++)
                    {
                        PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y + i});
                    }
                    mShips.erase(mShips.begin() + mCurrShipId);
                    mCurrShipId = -1;
                }
            }
        }
    }
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

            float sizeOfShip = 0;

            switch (type)
            {
            case CellState::SHIP_1:
                sizeOfShip = 1;
                break;
            case CellState::SHIP_2:
                sizeOfShip = 2;
                break;
            case CellState::SHIP_3:
                sizeOfShip = 3;
                break;
            case CellState::SHIP_4:
                sizeOfShip = 4;
                break;
            }

            if (!rotate)
            {
                if (CheckCollisionPointRec(
                        GetMousePosition(),
                        Rectangle{pos.x, pos.y, (Global::sizeOfTile * sizeOfShip - 1), (Global::sizeOfTile - 1)}))
                {
                    mCurrShipId = i;
                }
            }
            else
            {
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile - 1),
                                                                         (Global::sizeOfTile * sizeOfShip - 1)}))
                {
                    mCurrShipId = i;
                }
            }
        }
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        mCurrShipId = -1;
    }
}
