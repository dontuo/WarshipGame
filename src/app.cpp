#include "app.hpp"
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
                if(mPlayers[!mCurrPlayerTurn ? 0 : 1].CheckCellCollision(GetMousePosition(), Vector2 {x,y}))
                {
                    switch(mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y])
                    {
                        case CellState::SHIP_1:
                            mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_1_HITTED;
                        break;
                        case CellState::SHIP_2:
                            mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_2_HITTED;
                        break;
                        case CellState::SHIP_3:
                            mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_3_HITTED;
                        break;
                        case CellState::SHIP_4:
                            mPlayers[!mCurrPlayerTurn ? 0 : 1].mCells[x][y] = CellState::SHIP_4_HITTED;
                        break;
                        
                        //saw in someone's code something like this. Didn't know that I can do it like that :D
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
