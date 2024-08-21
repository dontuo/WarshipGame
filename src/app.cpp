#include "app.h"
#include "button.h"
#include <stdexcept>

App::App(){}

void App::Init()
{
    InitWindow(mWindowWidth, mWindowHeight, "Warship game");
    SetTargetFPS(60);

    mCrosshairTexture = LoadTexture("textures/crosshair.png");
    mShip1Texture = LoadTexture("textures/ship_1.png");

    if(!IsTextureReady(mCrosshairTexture))
    {
        throw std::runtime_error("failed to load crosshair texture");
    }
    HideCursor();
}

void App::Run()
{

    while(!WindowShouldClose())
    {
        if(!mShouldDrawMenu)
            DrawMenu();
        else
            Draw();
    }
}

void App::Draw()
{
    BeginDrawing();
        ClearBackground(DARKGRAY);
        
        int row = 10;
        int column = 10;
        int size = 40;
        static int offsetX = 50;
        static int offsetY = 250;
       
        for(int x = 0; x <= row; x++)
            DrawLine(x * size + offsetX,offsetY,x * size + offsetX, column * size + offsetY, WHITE);
    
        for(int y = 0; y <= column; y++)
            DrawLine(offsetX - 1,y * size + offsetY,row * size + offsetX,y * size + offsetY,WHITE);
        
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            offsetX++;
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            offsetY++;

        DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10,WHITE);
    EndDrawing();
};

void App::DrawMenu()
{
    static Button button(Rectangle{GetScreenWidth() / 2.f - 2,GetScreenHeight() / 2.f + 3,109,49});
    BeginDrawing();
    ClearBackground(DARKGRAY);

    if(button.IsMouseOverButton())
    {
        button.Draw(DARKBLUE);
    }
    if(button.IsButtonPressed(MOUSE_BUTTON_LEFT))
    {
        mShouldDrawMenu = 1;
    }

    DrawText("Warship Game",GetScreenWidth() / 3.5f, GetScreenHeight() / 3, 50, WHITE);
    DrawText("Play",GetScreenWidth() / 2.f, GetScreenHeight() / 2, 50, WHITE);
    

    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10,WHITE);

    EndDrawing();
};
