#include "app.hpp"
#include "board.hpp"
#include "cell.hpp"
#include "gamestate.hpp"
#include "global.hpp"
#include "raylib.h"
#include "raymath.h"

void App::Run()
{
    while (!WindowShouldClose())
    {
        switch (Global::gameState)
        {
        case GameState::MENU:
            UpdateMenu();
            break;
        case GameState::PLACING_SHIPS:
            /*int row = 10;
            int column = 10;
            int size = 40;
            static int offsetX = 100;
            static int offsetY = 250;*/
            UpdateShipPlacement();
            break;
        case GameState::GAME:
            UpdateGame();
            break;
        }
    }
}

void App::UpdateShipPlacement()
{
    DrawShipPlacement();
    ShipPlacementInputHandler();
}

void App::DrawShipPlacement()
{
    BeginDrawing();
    ClearBackground(Global::backgroundColor);
    if (mCurrPlayer->mShips.size() == 0)
    {
        Button button = Button(Rectangle{Global::windowWidth - 227, Global::windowHeight - 75, 154, 52});
        button.Draw(BLACK);
        DrawText("Ready", Global::windowWidth - 225, Global::windowHeight - 75, 50, WHITE);
    }

    mCurrPlayer->Draw(Global::offsetX, Global::offsetY, 0);
    DrawText(mCurrPlayer->mName.c_str(), 20, 0, 50, WHITE);

    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
}

void App::ShipPlacementInputHandler()
{
    mCurrPlayer->UpdateCurrShip();
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {

        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
                if (mCurrPlayer->CheckCellCollision(GetMousePosition(), Vector2{x, y}))
                    mCurrPlayer->HandleShipPlacement(x, y);
    }
    if (mCurrPlayer->mShips.size() == 0)
    {
        Button button = Button(Rectangle{Global::windowWidth - 227, Global::windowHeight - 75, 154, 52});

        if (button.IsButtonPressed(MOUSE_BUTTON_LEFT) && mCurrPlayer == &mPlayers[1])
            Global::gameState = GameState::GAME;
        else if (button.IsButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mCurrPlayer = &mPlayers[1];
        }
    }
    mCurrPlayer->HandleShipSelection();
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
        Global::gameState = GameState::PLACING_SHIPS;
}

void App::UpdateMenu()
{
    static Button menuButton(Rectangle{GetScreenWidth() / 2.f - 2, GetScreenHeight() / 2.f + 3, 109, 49});
    MenuInputHandler(menuButton);
    DrawMenu(menuButton);
}

void App::UpdateGame()
{
    GameInputHandler();
    DrawGame();
}
void App::DrawGame()
{
    BeginDrawing();
    ClearBackground(Global::backgroundColor);
    mPlayers[0].Draw(100, 100, 1);
    mPlayers[1].Draw(700, 100, 1);
    DrawText(mPlayers[0].mName.c_str(), 100, 50, 50, WHITE);
    DrawText(mPlayers[1].mName.c_str(), 700, 50, 50, WHITE);
    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    DrawText((mPlayers[mCurrPlayerTurn ? 0 : 1].mName + " turn").c_str(), 100, 600, 50, WHITE);
    EndDrawing();
}
void App::GameInputHandler()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].CheckCellCollision(GetMousePosition(), Vector2{x, y}))
                {
                    switch (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y])
                    {
                    case CellState::SHIP_1: {
                        mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_1_HITTED;

                        int width = 3;
                        int height = 3;

                        Rectangle bounds = ClampRectangleToBounds(x - 1, y - 1, width, height);

                        for (int i = 0; i < bounds.width; i++)
                            for (int j = 0; j < bounds.height; j++)
                            {
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[static_cast<int>(bounds.x) + i][static_cast<int>(bounds.y) + j] != CellState::SHIP_1_HITTED)
                                    mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[static_cast<int>(bounds.x) + i][static_cast<int>(bounds.y) + j] = CellState::MISSED;
                            }
                    }
                    break;

                    case CellState::SHIP_2: {
                        mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_2_HITTED;
                        // if(mPlayers[!mCurrPlayerTurn ? 0 : 1].CountCellsInArea(Rectangle{x - 1, y - 1, 3, 3}, CellState::SHIP_2_HITTED) == 2)
                        {
                            int countOfShip2Hitted = 0;
                            bool rotated = false;
                            bool onTop = false;
                            bool onLeft = false;
                            if (x - 1 >= 0)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x - 1][y] == CellState::SHIP_2_HITTED)
                                {
                                    onLeft = true;
                                    countOfShip2Hitted++;
                                }
                            if (x + 1 < 10)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 1][y] == CellState::SHIP_2_HITTED)
                                    countOfShip2Hitted++;
                            if (y - 1 >= 0)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y - 1] == CellState::SHIP_2_HITTED)
                                {
                                    countOfShip2Hitted++;
                                    rotated = true;
                                    onTop = true;
                                }
                            if (y + 1 < 10)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + 1] == CellState::SHIP_2_HITTED)
                                {
                                    countOfShip2Hitted++;
                                    rotated = true;
                                }

                            if (countOfShip2Hitted)
                            {
                                if (rotated)
                                {
                                    Rectangle rect = ClampRectangleToBounds(x - 1, y - 1 - (onTop ? 1 : 0), 3, 4);
                                    for (int i = 0; i < rect.width; i++)
                                        for (int j = 0; j < rect.height; j++)
                                        {
                                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] != CellState::SHIP_2_HITTED)
                                                mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] = CellState::MISSED;
                                        }
                                }
                                else
                                {
                                    Rectangle rect = ClampRectangleToBounds(x - 1 - (onLeft ? 1 : 0), y - 1, 4, 3);
                                    for (int i = 0; i < rect.width; i++)
                                        for (int j = 0; j < rect.height; j++)
                                        {
                                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] != CellState::SHIP_2_HITTED)
                                                mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] = CellState::MISSED;
                                        }
                                }
                                // mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 1][y + 1] = CellState::MISSED;
                            }
                        }
                    }
                    break;

                    case CellState::SHIP_3: {
                        mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_3_HITTED;
                        int countOfShip3Hitted = 0;
                        bool rotated = false;
                        bool onTop = false;
                        bool lastPartOfShip = false;
                        Rectangle rect = {};

                        Rectangle clamped = {};

                        clamped = ClampRectangleToBounds(x, y, 3, 1);

                        // that's fucking shit
                        if ((x - 1 >= 0) && (x + 1 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x - 1][y] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 1][y] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 2, y - 1, 5, 3);
                            }
                        }

                        if ((x - 2 >= 0) && (x + 1 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x - 1][y] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x - 2][y] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 1][y] != CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 3, y - 1, 5, 3);
                            }
                        }
                        else if ((x - 2 >= 0) && !(x + 1 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x - 1][y] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x - 2][y] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 3, y - 1, 5, 3);
                            }
                        }

                        if ((x - 1 >= 0) && (x + 2 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x - 1][y] != CellState::SHIP_3 && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 1][y] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 2][y] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 1, y - 1, 5, 3);
                            }
                        }
                        else if (!(x - 1 >= 0) && (x + 2 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 1][y] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + 2][y] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 1, y - 1, 5, 3);
                            }
                        }

                        if ((y - 1 >= 0) && (y + 1 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y - 1] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + 1] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 1, y - 2, 3, 5);
                            }
                        }

                        if ((y - 2 >= 0) && (y + 1 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y - 1] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y - 2] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + 1] != CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 1, y - 3, 3, 5);
                            }
                        }
                        else if ((y - 2 >= 0) && (y + 1 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y - 1] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y - 2] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 1, y - 3, 3, 5);
                            }
                        }

                        if ((y - 1 >= 0) && (y + 2 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y - 1] != CellState::SHIP_3 && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + 1] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + 2] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 1, y - 1, 3, 5);
                            }
                        }
                        else if (!(y - 1 >= 0) && (y + 2 < 10))
                        {
                            if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + 1] == CellState::SHIP_3_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + 2] == CellState::SHIP_3_HITTED)
                            {
                                rect = ClampRectangleToBounds(x - 1, y - 1, 3, 5);
                            }
                        }

                        // someone who reads this code, please, make it better :3

                        if (rect.width != 0 && rect.height != 0)
                            for (int i = 0; i < rect.width; i++)
                                for (int j = 0; j < rect.height; j++)
                                {
                                    if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] != CellState::SHIP_3_HITTED)
                                        mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] = CellState::MISSED;
                                }
                    }
                    break;

                    case CellState::SHIP_4: {
                        Rectangle rect = {};
                        mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_4_HITTED;

                        if ((x - 1 >= 0) && (x + 3 < 10))
                        {
                            int count = 0;
                            for (int i = -1; i < 4; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + i][y] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 1, 6, 3);
                        }
                        else if (!(x - 1 >= 0) && (x + 3 < 10))
                        {
                            int count = 0;
                            for (int i = 0; i < 4; i++)
                                if (mPlayers[!mCurrPlayer ? 0 : 1].mCells[x + i][y] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 1, 6, 3);
                        }

                        if ((x - 1 >= 0) && (x + 2 < 10))
                        {
                            int count = 0;
                            for (int i = -1; i < 3; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + i][y] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 2, y - 1, 6, 3);
                        }

                        if ((x - 2 >= 0) && (x + 1 < 10))
                        {
                            int count = 0;
                            for (int i = -2; i < 2; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + i][y] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 4, y - 1, 6, 3);
                        }

                        if ((x - 3 >= 0) && (x + 1 < 10))
                        {
                            int count = 0;
                            for (int i = -3; i < 2; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + i][y] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 4, y - 1, 6, 3);
                        }
                        else if ((x - 3 >= 0) && !(x + 1 < 10))
                        {
                            int count = 0;
                            for (int i = -3; i < 1; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x + i][y] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 4, y - 1, 6, 3);
                        }

                        //
                        if ((y - 1 >= 0) && (y + 3 < 10))
                        {
                            int count = 0;
                            for (int i = -1; i < 4; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + i] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 1, 3, 6);
                        }
                        else if (!(y - 1 >= 0) && (y + 3 < 10))
                        {
                            int count = 0;
                            for (int i = 0; i < 4; i++)
                                if (mPlayers[!mCurrPlayer ? 0 : 1].mCells[x][y + i] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 1, 3, 6);
                        }

                        if ((y - 1 >= 0) && (y + 2 < 10))
                        {
                            int count = 0;
                            for (int i = -1; i < 3; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + i] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 2, 3, 6);
                        }

                        if ((y - 2 >= 0) && (y + 1 < 10))
                        {
                            int count = 0;
                            for (int i = -2; i < 2; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + i] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 4, 3, 6);
                        }

                        if ((y - 3 >= 0) && (y + 1 < 10))
                        {
                            int count = 0;
                            for (int i = -3; i < 2; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + i] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 4, 3, 6);
                        }
                        else if ((y - 3 >= 0) && !(y + 1 < 10))
                        {
                            int count = 0;
                            for (int i = -3; i < 1; i++)
                                if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y + i] == CellState::SHIP_4_HITTED)
                                    count++;

                            if (count == 4)
                                rect = ClampRectangleToBounds(x - 1, y - 4, 3, 6);
                        }

                        if (rect.width != 0 && rect.height != 0)
                            for (int i = 0; i < rect.width; i++)
                                for (int j = 0; j < rect.height; j++)
                                {
                                    if (mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] != CellState::SHIP_4_HITTED && mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] != CellState::SHIP_4)
                                        mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[(int)rect.x + i][(int)rect.y + j] = CellState::MISSED;
                                }
                    }
                    break;

                    // saw in someone's code this. Didn't know that I can do that :D
                    case CellState::SHIP_1_HITTED:
                    case CellState::SHIP_2_HITTED:
                    case CellState::SHIP_3_HITTED:
                    case CellState::SHIP_4_HITTED:
                    case CellState::HIT:
                    case CellState::MISSED:
                        break;

                    default:
                        mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::MISSED;
                        mCurrPlayerTurn = !mCurrPlayerTurn;
                        break;
                    }
                }
            }
        }
    }
}

App::App()
{
    // TODO a resizable window in future updates
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Warship game");
    // InitWindow(mWindowWidth, mWindowHeight, "Warship game");
    SetWindowSize(Global::windowWidth, Global::windowHeight);
    SetTargetFPS(120);

    mCrosshairTexture = LoadTexture("textures/crosshair.png");

    if (!IsTextureReady(mCrosshairTexture))
    {
        throw std::runtime_error("failed to load crosshair texture");
    }
    HideCursor();

    LoadTextures();

    mPlayers.push_back(Player("Player 1"));
    mPlayers.push_back(Player("Player 2"));

    mCurrPlayer = &mPlayers[0];
}
