#include "app.h"
#include "raylib.h"
#include <raymath.h>
App::App(){}

void App::Init()
{
    InitWindow(800, 600, "lol");
    SetTargetFPS(60);
}

void App::Run()
{
    while(!WindowShouldClose())
    {
        DrawMenu();    
    }
}

void App::Draw()
{
BeginDrawing();
    static Vector2 size{10,10};
    static Vector2 position{GetMousePosition()};

    position = Vector2Lerp(position,GetMousePosition(), 0.1f);
    size.x += GetMouseWheelMove() * 5;
    size.y += GetMouseWheelMove() * 5;
    ClearBackground(DARKGRAY);
    DrawRectangleV(position ,size, Color{255,255,255, 255});
EndDrawing();
};

void App::DrawMenu()
{
BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawText("Warship Game",GetScreenWidth() / 3.5f, GetScreenHeight() / 3, 50, WHITE);
    DrawText("Play",GetScreenWidth() / 2.f, GetScreenHeight() / 2, 50, WHITE);
    GetScreenWidth();
    GetScreenHeight();
EndDrawing();
};
