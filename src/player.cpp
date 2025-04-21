#include "player.hpp"
#include "cell.hpp"
#include "raylib.h"

Player::Player(std::string name) : mPlayerName(name), Board(0, 0)
{
    InitShips();
}

void Player::InitShips()
{

    int x = Global::windowWidth - 500;
    int y = 150;

    for (int i = 0; i < 4; i++)
    {
        mUnplacedShips.push_back(Ship{Vector2{x, y},Vector2{x, y}, CellState::SHIP_1});

        x += 100;
    }
    x = Global::windowWidth - 500;
    y = 225; // boat 1x2, 3 pieces only: ##
    for (int i = 0; i < 3; i++)
    {
        mUnplacedShips.push_back(Ship{Vector2{x, y},Vector2{x, y}, CellState::SHIP_2});

        x += 100 + (Global::sizeOfTile - 1);
    }
    x = Global::windowWidth - 500;
    y = 300;
    // boat 1x3, 2 pieces only: ###
    for (int i = 0; i < 2; i++)
    {

        mUnplacedShips.push_back(Ship{Vector2{x, y},Vector2{x, y}, CellState::SHIP_3});

        x += 100 + (Global::sizeOfTile - 1) * 2;
    }

    x = Global::windowWidth - 500;
    y = 375;

    // boat 1x4, 1 pieces only: ####
    for (int i = 0; i < 1; i++)
    {
        mUnplacedShips.push_back(Ship{Vector2{x, y},Vector2{x, y}, CellState::SHIP_4});

        x += 100 + (Global::sizeOfTile - 1) * 3;
    }
}

void Player::Draw(int offsetX, int offsetY, bool hide = 0)
{
    SetOffset(offsetX, offsetY);

    Board::Draw(hide);

    using namespace Global; // for sizeOfTile

    if (mCurrShipId != -1)
    {
        int rotate = mUnplacedShips[mCurrShipId].rotate;

        int sizeOfShip = 0;

        switch (mUnplacedShips[mCurrShipId].mCellState)
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
                                DrawShip(mUnplacedShips[mCurrShipId], x * sizeOfTile + GetOffset().x, y * sizeOfTile + 1 + GetOffset().y, RED);
                            }
                            else
                            {
                                DrawShip(mUnplacedShips[mCurrShipId], x * sizeOfTile + GetOffset().x, y * sizeOfTile + 1 + GetOffset().y, GREEN);
                            }
                    }
                    else
                    {
                        if (y < 11 - sizeOfShip)
                            if (!IsAreaEmpty(x - 1, y - 1, 3, 2 + sizeOfShip))
                                DrawShip(mUnplacedShips[mCurrShipId], x * sizeOfTile + GetOffset().x, y * sizeOfTile + 1 + GetOffset().y, RED);
                            else
                                DrawShip(mUnplacedShips[mCurrShipId], x * sizeOfTile + GetOffset().x, y * sizeOfTile + 1 + GetOffset().y, GREEN);
                    }
                }
            }
    }

    for (int i = 0; i < mUnplacedShips.size(); i++)
    {
        Vector2 &pos = mUnplacedShips[i].mPos;
        CellState &type = mUnplacedShips[i].mCellState;
        DrawShip(mUnplacedShips[i], pos, WHITE);
    }
}

void Player::HandleShipPlacement(int x, int y)
{
    if (mCurrShipId != -1)
    {
        bool rotate = mUnplacedShips[mCurrShipId].rotate;

        int sizeOfShip = 0;

        switch (mUnplacedShips[mCurrShipId].mCellState)
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
                        SetCellState(Vector2{x + i, y}, mUnplacedShips[mCurrShipId].mCellState);
                    }
                    mUnplacedShips.erase(mUnplacedShips.begin() + mCurrShipId);
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
                        SetCellState(Vector2{x, y + i}, mUnplacedShips[mCurrShipId].mCellState);
                    }
                    mUnplacedShips.erase(mUnplacedShips.begin() + mCurrShipId);
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
            mUnplacedShips[mCurrShipId].rotate = !mUnplacedShips[mCurrShipId].rotate;

        Vector2 mousePos = GetMousePosition();

        Vector2 &shipPos = mUnplacedShips[mCurrShipId].mPos;
        mousePos.x -= 22;
        mousePos.y -= 22;

        shipPos = GetSplinePointLinear(mousePos, shipPos, 0.7f);
    }
}

void Player::HandleShipSelection()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < mUnplacedShips.size(); i++)
        {
            Vector2 pos = mUnplacedShips[i].mPos;
            CellState type = mUnplacedShips[i].mCellState;
            bool rotate = mUnplacedShips[i].rotate;

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
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile * sizeOfShip - 1), (Global::sizeOfTile - 1)}))
                {
                    mCurrShipId = i;
                }
            }
            else
            {
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, (Global::sizeOfTile - 1), (Global::sizeOfTile * sizeOfShip - 1)}))
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
