#include "app.hpp"
#include "board.hpp"
#include "cell.hpp"
#include "raylib.h"

void App::Run()
{
    while (!WindowShouldClose())
    {
        if (mShouldDrawMenu)
        { // drawing menu untill play button is pressed
            UpdateMenu();
        }
        else
        {
            // drawing game itself
            UpdateGame();
            /*int row = 10;
            int column = 10;
            int size = 40;
            static int offsetX = 100;
            static int offsetY = 250;*/
        }
    }
}

void App::UpdateGame()
{
    // static Grid grid(10, 10, 45, 100, 250);
    static Board board(100, 250);

    DrawGame(board);
    GameInputHandler(board);
}

void App::DrawGame(Board &board)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    board.Draw(0);

    if (mCurrShipId != -1)
        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
            {
                if (board.CheckCollision(GetMousePosition(), Vector2{x, y}))
                {
                    switch (mShips[mCurrShipId].mCellState)
                    {
                        case CellState::SHIP_1:
                            if (!board.IsAreaEmpty(x, y, 1))
                                DrawShip(CellState::SHIP_1, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                         RED);
                            else
                                DrawShip(CellState::SHIP_1, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                         GREEN);
                            break;

                        case CellState::SHIP_2:
                            if (x < 9)
                                if (!board.IsAreaEmpty(x, y, 2))
                                    DrawShip(CellState::SHIP_2, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                             RED);
                                else
                                    DrawShip(CellState::SHIP_2, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                             GREEN);
                            break;

                        case CellState::SHIP_3:
                            if (x < 8)

                                if (!board.IsAreaEmpty(x, y, 3))
                                    DrawShip(CellState::SHIP_3, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                             RED);
                                else
                                    DrawShip(CellState::SHIP_3, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                             GREEN);
                            break;

                        case CellState::SHIP_4:
                            if (x < 7)
                                if (!board.IsAreaEmpty(x, y, 4))
                                    DrawShip(CellState::SHIP_4, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                             RED);
                                else
                                    DrawShip(CellState::SHIP_4, x * 45 + board.mOffset.x, y * 45 + 1 + board.mOffset.y,
                                             GREEN);
                            break;
                    }
                }
            }

    for (int i = 0; i < mShips.size(); i++)
    {
        Vector2 &pos = mShips[i].mPos;
        CellState &type = mShips[i].mCellState;
        DrawShip(type, pos, WHITE);
    }

    DrawText("Player1", 20, 0, 50, WHITE);
    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
};

void App::GameInputHandler(Board &board)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < mShips.size(); i++)
        {
            Vector2 pos = mShips[i].mPos;
            CellState type = mShips[i].mCellState;
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x, pos.y, 44, 44}))
            {
                mCurrShipId = i;
            }
        }

        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                if (board.CheckCollision(GetMousePosition(), Vector2{x, y}))
                    switch (mShips[mCurrShipId].mCellState)
                    {
                        case CellState::SHIP_1:
                            if (board.IsAreaEmpty(x, y, 1))
                            {
                                HandleShipPlacement(x, y, board);
                                // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                                mShips.erase(mShips.begin() + mCurrShipId);
                                mCurrShipId = -1;
                            }
                            break;

                        case CellState::SHIP_2:
                            if (x < 9)
                            {
                                if (board.IsAreaEmpty(x, y, 2))
                                {
                                    HandleShipPlacement(x, y, board);
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
                                    mShips.erase(mShips.begin() + mCurrShipId);
                                    mCurrShipId = -1;
                                }
                            }
                            break;

                        case CellState::SHIP_3:
                            if (x < 8)
                            {
                                if (board.IsAreaEmpty(x, y, 3))
                                {

                                    HandleShipPlacement(x, y, board);
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2, y});
                                    mShips.erase(mShips.begin() + mCurrShipId);
                                    mCurrShipId = -1;
                                }
                            }
                            break;

                        case CellState::SHIP_4:
                            if (x < 7)
                            {
                                if (board.IsAreaEmpty(x, y, 4))
                                {
                                    HandleShipPlacement(x, y, board);
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2, y});
                                    // board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 3, y});
                                    mShips.erase(mShips.begin() + mCurrShipId);
                                    mCurrShipId = -1;
                                }
                            }
                            break;
                    }
            }
        }
    }

    if (mCurrShipId != -1)
    {
        Vector2 mousePos = GetMousePosition();

        Vector2 &shipPos = mShips[mCurrShipId].mPos;
        mousePos.x -= 22;
        mousePos.y -= 22;

        shipPos = GetSplinePointLinear(mousePos, shipPos, 0.7f);
    }
}

void App::HandleShipPlacement(int x, int y, Board &board)
{
    switch (mShips[mCurrShipId].mCellState)
    {
        case CellState::SHIP_1:
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
            break;
        case CellState::SHIP_2:
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
            break;
        case CellState::SHIP_3:
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2, y});

            break;
        case CellState::SHIP_4:
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x, y});
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1, y});
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2, y});
            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 3, y});
            break;
    }
}
void App::DrawMenu(Button &menuButton)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    if (menuButton.IsMouseOverButton())
        menuButton.Draw(DARKBLUE);

    DrawText("Warship Game", GetScreenWidth() / 3.5f, GetScreenHeight() / 3, 50, WHITE);
    DrawText("Play", GetScreenWidth() / 2.f, GetScreenHeight() / 2, 50, WHITE);

    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
};

void App::MenuInputHandler(Button &menuButton)
{
    if (menuButton.IsButtonPressed(MOUSE_BUTTON_LEFT))
    {
        mShouldDrawMenu = 0;
    }
}

void App::UpdateMenu()
{
    static Button menuButton(Rectangle{GetScreenWidth() / 2.f - 2, GetScreenHeight() / 2.f + 3, 109, 49});
    MenuInputHandler(menuButton);
    DrawMenu(menuButton);
}

App::App()
{
    // TODO a resizable window in future updates
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(mWindowWidth, mWindowHeight, "Warship game");
    SetTargetFPS(120);

    mCrosshairTexture = LoadTexture("textures/crosshair.png");

    if (!IsTextureReady(mCrosshairTexture))
    {
        throw std::runtime_error("failed to load crosshair texture");
    }
    HideCursor();

    InitShips();
}

void App::InitShips()
{
    LoadTextures();

    for (int i = 0; i < 4; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 150;

        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_1});

        x += 100;
    }

    // boat 1 by 2, 3 pieces only: ##
    for (int i = 0; i < 3; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 225;

        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_2});

        x += 100 + 44;
    }

    // boat 1 by 3, 2 pieces only: ###
    for (int i = 0; i < 2; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 300;

        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_3});

        x += 100 + 44 * 2;
    }

    // boat 1 by 4, 1 pieces only: ####
    for (int i = 0; i < 1; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 375;

        mShips.push_back(Ship{Vector2{x, y}, CellState::SHIP_4});

        x += 100 + 44 * 3;
    }
}
