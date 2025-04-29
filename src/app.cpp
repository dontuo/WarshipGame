#include "app.hpp"
#include "gamestate.hpp"
#include "global.hpp"
#include "raylib.h"
#include <cstdint>
#define CLAY_IMPLEMENTATION
#include <clay.h>
#include <renderers/raylib/clay_renderer_raylib.c>

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
            UpdateShipPlacement();
            break;
        case GameState::GAME:
            UpdateGame();
            break;

        case GameState::END_GAME:
            UpdateEndGame();
        }
    }
}

// Main menu
void App::UpdateMenu()
{
    MenuInputHandler();
    DrawMenu();
}

void App::DrawMenu()
{
    Clay_Sizing layoutExpand = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)};

    Clay_BeginLayout();

    CLAY({
        .id = CLAY_ID("background"),
        .layout =
            {
                .sizing = layoutExpand,
                .padding = {350, 350, 100, 100},
                .childGap = 50,
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            },
        .image = {.imageData = &mBackgroundTexture, .sourceDimensions = {1024, 1536}},
    })
    {
        CLAY({
                 .id = CLAY_ID("Battleship"),
                 .layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(50)}, .childGap = 100, .childAlignment = {.x = CLAY_ALIGN_X_CENTER}},
                 .cornerRadius = 10,
             }, )
        {
            CLAY_TEXT(CLAY_STRING("Battleship Game"), CLAY_TEXT_CONFIG({
                                                          .textColor = {255, 255, 255, 255},
                                                          .fontId = 0,
                                                          .fontSize = 48,
                                                          .letterSpacing = 0,
                                                          .lineHeight = 0,
                                                          .textAlignment = CLAY_TEXT_ALIGN_RIGHT,
                                                      }));
        };

        CLAY({
            .id = CLAY_ID("Button1"),
            .layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(50)}, .childGap = 100, .childAlignment = {.x = CLAY_ALIGN_X_CENTER}},
            .backgroundColor = {18, 43, 68, Clay_Hovered() ? 255 : 200},
            .cornerRadius = 10,
        })
        {
            CLAY_TEXT(CLAY_STRING("Play"), CLAY_TEXT_CONFIG({
                                               .textColor = {255, 255, 255, 255},
                                               .fontId = 0,
                                               .fontSize = 48,
                                               .letterSpacing = 0,
                                               .lineHeight = 0,
                                               .textAlignment = CLAY_TEXT_ALIGN_RIGHT,
                                           }));
        };

        CLAY({
            .id = CLAY_ID("Button2"),
            .layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(50)}, .childAlignment = {.x = CLAY_ALIGN_X_CENTER}},
            .backgroundColor = {18, 43, 68, Clay_Hovered() ? 255 : 200},
            .cornerRadius = 10,

        })
        {
            CLAY_TEXT(CLAY_STRING("Exit"), CLAY_TEXT_CONFIG({
                                               .textColor = {255, 255, 255, 255},
                                               .fontId = 0,
                                               .fontSize = 48,
                                               .letterSpacing = 0,
                                               .lineHeight = 0,
                                               .textAlignment = CLAY_TEXT_ALIGN_RIGHT,
                                           }));
        };
    };

    Clay_RenderCommandArray renderCommands = Clay_EndLayout();

    BeginDrawing();

    ClearBackground(DARKGRAY);
    Clay_Raylib_Render(renderCommands, fonts);
    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
};

void App::MenuInputHandler()
{
    UpdateClay();

    bool button1 = Clay_PointerOver(Clay_GetElementId(CLAY_STRING("Button1"))) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool button2 = Clay_PointerOver(Clay_GetElementId(CLAY_STRING("Button2"))) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (button1)
    {
        Global::gameState = GameState::PLACING_SHIPS;
    }

    if (button2)
    {
        Clay_Raylib_Close();
        return;
    }

    static bool debugEnabled = 0;
    if (IsKeyPressed(KEY_D))
    {
        debugEnabled = !debugEnabled;
        Clay_SetDebugModeEnabled(debugEnabled);
    }
}
//------------------------------------------------------------

// Ship placement
void App::UpdateShipPlacement()
{
    ShipPlacementInputHandler();
    DrawShipPlacement();
}

void App::DrawShipPlacement()
{
    BeginDrawing();
    ClearBackground(Global::backgroundColor);
    if (mCurrPlayer->mUnplacedShips.size() == 0)
    {
        Button button = Button(Rectangle{Global::windowWidth - 227, Global::windowHeight - 75, 154, 52});
        button.Draw(BLACK);
        DrawText("Ready", Global::windowWidth - 225, Global::windowHeight - 75, 50, WHITE);
    }

    mCurrPlayer->Draw(Global::offsetX, Global::offsetY, 0);
    DrawText(mCurrPlayer->mPlayerName.c_str(), 20, 0, 50, WHITE);

    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
}

void App::ShipPlacementInputHandler()
{
    UpdateClay();
    mCurrPlayer->UpdateCurrShip();
    int currShipId = mCurrPlayer->mCurrShipId;
    Vector2 &shipPose = mCurrPlayer->mUnplacedShips[currShipId].mPos;
    Vector2 &originPlace = mCurrPlayer->mUnplacedShips[currShipId].mOriginPlace;
    bool &rotate = mCurrPlayer->mUnplacedShips[currShipId].rotate;

    if (mCurrPlayer->mUnplacedShips.size() == 0)
    {
        Button button = Button(Rectangle{Global::windowWidth - 227, Global::windowHeight - 75, 154, 52});

        if (button.IsButtonPressed(MOUSE_BUTTON_LEFT) && mCurrPlayer == &mPlayers[1])
            Global::gameState = GameState::GAME;
        else if (button.IsButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mCurrPlayer = &mPlayers[1];
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
            {
                if (mCurrPlayer->CheckCellCollision(GetMousePosition(), Vector2{x, y}))
                {
                    mCurrPlayer->HandleShipPlacement(x, y);
                }
                else
                {
                    shipPose = originPlace;
                }
            }
    }

    if (shipPose.x == originPlace.x && shipPose.y == originPlace.y)
    {
        rotate = 0;
    }

    mCurrPlayer->HandleShipSelection();
}
//------------------------------------------------------------

// The game itself (game logick)
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
    DrawText(mPlayers[0].mPlayerName.c_str(), 100, 50, 50, WHITE);
    DrawText(mPlayers[1].mPlayerName.c_str(), 700, 50, 50, WHITE);
    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    DrawText((mPlayers[mCurrPlayerTurn ? 0 : 1].mPlayerName + " turn").c_str(), 100, 600, 50, WHITE);
    EndDrawing();
}

void App::GameInputHandler()
{
    Player &targetPlayer = mPlayers[!mCurrPlayerTurn ? 0 : 1];

    if (IsPlayerDefeated(targetPlayer))
    {
        Global::gameState = GameState::END_GAME;
    }

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (!targetPlayer.CheckCellCollision(GetMousePosition(), Vector2{x, y}))
                continue;

            switch (targetPlayer.GetCellState(x, y))
            {
            case CellState::SHIP_1:
                targetPlayer.SetCellState(x, y, CellState::HIT);
                break;
            case CellState::SHIP_2:
                targetPlayer.SetCellState(x, y, CellState::HIT);
                break;
            case CellState::SHIP_3:
                targetPlayer.SetCellState(x, y, CellState::HIT);
                break;
            case CellState::SHIP_4:
                targetPlayer.SetCellState(x, y, CellState::HIT);
                break;

            case CellState::SHIP_1_HITTED:
            case CellState::SHIP_2_HITTED:
            case CellState::SHIP_3_HITTED:
            case CellState::SHIP_4_HITTED:
            case CellState::HIT:
            case CellState::MISSED:
                break;

            default:
                targetPlayer.SetCellState(x, y, CellState::MISSED);
                mCurrPlayerTurn = !mCurrPlayerTurn;
                break;
            }
        }
    }

    targetPlayer.processHits();
}
//------------------------------------------------------------

bool App::IsPlayerDefeated(Player &player)
{
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            switch (player.GetCellState(x, y))
            {
            case CellState::SHIP_1:
            case CellState::SHIP_2:
            case CellState::SHIP_3:
            case CellState::SHIP_4:
                return false;
            }
        }
    }
    return true;
}

App::App()
{
    // raylib init
    Clay_Raylib_Initialize(Global::windowWidth, Global::windowHeight, "Warship game", FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(120);
    HideCursor();

    // clay init (for ui)
    uint64_t clayRequiredMemory = Clay_MinMemorySize();

    Clay_Arena clayMemory = (Clay_Arena){
        .nextAllocation = 0,
        .capacity = clayRequiredMemory,
        .memory = new char[clayRequiredMemory],
    };

    Clay_Initialize(clayMemory, Clay_Dimensions{.width = GetScreenWidth(), .height = GetScreenHeight()}, Clay_ErrorHandler{.errorHandlerFunction = [](Clay_ErrorData errorText) { std::cout << errorText.errorText.chars; }});

    mCrosshairTexture = LoadTexture("textures/crosshair.png");
    mBackgroundTexture = LoadTexture("textures/background.png");

    if (!IsTextureReady(mCrosshairTexture))
    {
        throw std::runtime_error("failed to load crosshair texture");
    }

    LoadTextures();

    fonts[0] = LoadFontEx("resources/RobotoMono-Medium.ttf", 48, 0, 400);
    SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    mPlayers.push_back(Player("Player 1"));
    mPlayers.push_back(Player("Player 2"));

    mCurrPlayer = &mPlayers[0];
}

void App::UpdateEndGame()
{
    EndGameInputHandler();
    DrawEndGame();
}

void App::EndGameInputHandler()
{
}

void App::DrawEndGame()
{
    BeginDrawing();

    ClearBackground(Global::backgroundColor);
    mPlayers[mCurrPlayerTurn ? 1 : 0].Draw(100, 100, 0);

    DrawText((mPlayers[!mCurrPlayerTurn ? 1 : 0].mPlayerName + " won").c_str(), 700, 100, 50, WHITE);
    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
}

App::~App()
{
    Clay_Raylib_Close();
}

void App::UpdateClay()
{
#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2(vector)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
    (Clay_Vector2)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \
        .x = vector.x, .y = vector.y                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
    }

    Clay_Vector2 mousePosition = RAYLIB_VECTOR2_TO_CLAY_VECTOR2(GetMousePosition());
    Clay_SetPointerState(mousePosition, IsMouseButtonDown(MOUSE_BUTTON_LEFT));

    Clay_Dimensions clayDimensions = {.width = GetScreenWidth(), .height = GetScreenHeight()};
    Clay_SetLayoutDimensions(clayDimensions);
}
