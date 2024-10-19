#include "app.hpp"
#include "global.hpp"
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
    DrawGame();
    GameInputHandler();
}

void App::DrawGame()
{
    BeginDrawing();
    ClearBackground(Global::backgroundColor);

    mCurrPlayer->Draw(Global::offsetX, Global::offsetY, 0);
    DrawText(mCurrPlayer->mName.c_str(), 20, 0, 50, WHITE);

    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
}

void App::GameInputHandler()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        mCurrPlayer->HandleShipSelection();

        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
                if (mCurrPlayer->CheckCellCollision(GetMousePosition(), Vector2{x, y}))
                    mCurrPlayer->HandleShipPlacement(x, y);
    }
    if(mCurrPlayer->mShips.size() == 0)
    {
        Button(Rectangle{Global::windowWidth - 227, Global::windowHeight - 75, 154, 52}).Draw(BLACK);
        DrawText("Ready", Global::windowWidth - 225, Global::windowHeight - 75, 50 ,WHITE);
    }
    mCurrPlayer->UpdateCurrShipPosition();
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
        mShouldDrawMenu = 0;
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
