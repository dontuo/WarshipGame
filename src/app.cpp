#include "app.hpp"

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

        case GameState::END_GAME:
            UpdateEndGame();
        }
    }
}

void App::DrawMenu(Button &menuButton)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    if (menuButton.IsMouseOverButton())
        menuButton.Draw(DARKBLUE);

    DrawText("Warship Game", Global::windowWidth / 3.5f, Global::windowHeight / 3, 50, WHITE);
    DrawText("Play", Global::windowWidth / 3.5f, Global::windowHeight / 2, 50, WHITE);

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
    static Button menuButton(Rectangle{Global::windowWidth / 3.5f - 2, Global::windowHeight / 2.f + 3, 109, 49});
    MenuInputHandler(menuButton);
    DrawMenu(menuButton);
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
    
    if(shipPose.x == originPlace.x && shipPose.y == originPlace.y)
    {
        rotate = 0;
    }
    
    mCurrPlayer->HandleShipSelection();
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
    DrawText(mPlayers[0].mPlayerName.c_str(), 100, 50, 50, WHITE);
    DrawText(mPlayers[1].mPlayerName.c_str(), 700, 50, 50, WHITE);
    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    DrawText((mPlayers[mCurrPlayerTurn ? 0 : 1].mPlayerName + " turn").c_str(), 100, 600, 50, WHITE);
    EndDrawing();
}

void App::GameInputHandler()
{
    Player &targetPlayer = mPlayers[!mCurrPlayerTurn ? 0 : 1];

    if(IsPlayerDefeated(targetPlayer))
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
                targetPlayer.SetCellState(x,y, CellState::HIT);
            break;
            case CellState::SHIP_2:
                targetPlayer.SetCellState(x,y, CellState::HIT);
            break;
            case CellState::SHIP_3:
                targetPlayer.SetCellState(x,y, CellState::HIT);
            break;
            case CellState::SHIP_4:
                targetPlayer.SetCellState(x,y, CellState::HIT);
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

bool App::IsPlayerDefeated(Player& player) 
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            switch (player.GetCellState(x,y)) {
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
    // TODO: a resizable window in future updates
    
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
    mPlayers[mCurrPlayerTurn ? 1 : 0].Draw(100,100, 0);

    DrawText((mPlayers[!mCurrPlayerTurn ? 1 : 0].mPlayerName + " won").c_str(), 700, 100, 50, WHITE);
    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10, WHITE);

    EndDrawing();
}
