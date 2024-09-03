#include "app.h"
#include "board.h"
#include "cell.h"
#include "grid.h"
#include "raymath.h"
#include "ship.h"
#include <raylib.h>
#include <stdexcept>

App::App(){}

void App::Init()
{
    // TODO a resizable window in future updates
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(mWindowWidth, mWindowHeight, "Warship game");
    SetTargetFPS(120);

    mCrosshairTexture = LoadTexture("textures/crosshair.png");
    
    if(!IsTextureReady(mCrosshairTexture))
    {
        throw std::runtime_error("failed to load crosshair texture");
    }
    HideCursor();

    SetRandomSeed(3);
    GetRandomValue(1,10);
    
    // boat 1 by 1, 4 pieces only: #
    for(int i = 0; i < 4; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 150;

        mShips.push_back(Ship{Vector2{x,y}, CellState::BOAT_1});
        //mShips[i].mPos = Vector2{x,y};
        //mShips[i].mCellState = CellState::BOAT_1;
        //mShip1[i].x = x
        //mShip1[i].y = y;

        x += 100;
    }

    // boat 1 by 2, 3 pieces only: ##
    for(int i = 0; i < 3; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 225;
        //mShip2[i].x = x;
        //mShip2[i].y = y;
        mShips.push_back(Ship{Vector2{x,y}, CellState::BOAT_2});
        //mShips[i].mPos = Vector2{x,y};
        //mShips[i].mCellState = CellState::BOAT_2;
        x += 100 + 44;
    }

    // boat 1 by 3, 2 pieces only: ###
    for(int i = 0; i < 2; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 300;
        //mShip3[i].x = x;
        //mShip3[i].y = y;
        mShips.push_back(Ship{Vector2{x,y}, CellState::BOAT_3});
        //mShips[i].mPos = Vector2{x,y};
        //mShips[i].mCellState = CellState::BOAT_3;

        x += 100 + 44 * 2;
    }

    // boat 1 by 4, 1 pieces only: ####
    for(int i = 0; i < 1; i++)
    {
        static int x = mWindowWidth - 500;
        static int y = 375;
        mShip4[i].x = x;
        mShip4[i].y = y;
        
        mShips.push_back(Ship{Vector2{x,y}, CellState::BOAT_4});
        //mShips[i].mPos = Vector2{x,y};
        //mShips[i].mCellState = CellState::BOAT_4;
        x += 100 + 44 * 3;
    }


    LoadTextures();
}

void App::Run()
{
    while(!WindowShouldClose())
    {
        if(mShouldDrawMenu)
        {
            UpdateMenu();         
        }
        else
        {
            
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
    
    static Grid grid(10, 10, 45, 100, 250);
        
    static Board board(100,250);
    
    //board.PrintCells();
    GameDraw(board);
    GameInputHandler(board);
}

void App::GameDraw(Board &board)
{
    //mMenuButton({Rectangle{GetScreenWidth() / 2.f - 2,GetScreenHeight() / 2.f + 3,109,49});
    BeginDrawing();
        ClearBackground(DARKGRAY);

        board.Draw(0); 
        
        
        //grid.Draw();
        //DrawTexture(mShip1Texture, GetMouseX(), GetMouseY(), RED);
        //DrawTexture(mShip1Texture, mWindowWidth - 500, 100, WHITE);
        //DrawTexture(mShip1Texture, mWindowWidth - 400, 100, WHITE);
        //DrawTexture(mShip1Texture, mWindowWidth - 300, 100, WHITE);
        
        //DrawTextureV(mShip1Texture, GetMousePosition(),WHITE);
        
        for (int i = 0; i < mShips.size(); i++)
        {
            Vector2 pos = mShips[i].mPos;
            CellState type = mShips[i].mCellState;
            DrawShip(type, pos.x, pos.y, WHITE);
        }
        /*
        for(int i = 0; i < mShip1.size(); i++)
            DrawShip(CellState::BOAT_1, mShip1[i].x, mShip1[i].y, WHITE);
        for(int i = 0; i < mShip2.size(); i++)
            DrawShip(CellState::BOAT_2, mShip2[i].x, mShip2[i].y,WHITE);

        for(int i = 0; i < mShip3.size(); i++)
            DrawShip(CellState::BOAT_3, mShip3[i].x, mShip3[i].y, WHITE);
        
        for(int i = 0; i < mShip4.size(); i++)
            DrawShip(CellState::BOAT_4, mShip4[i].x, mShip4[i].y, WHITE);
        */
        {
        
    }

        DrawText("Player1",20,0,50,WHITE);
        DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10,WHITE);
    EndDrawing();
};

void App::GameInputHandler(Board &board)
{
    /*if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (x >= 10)
        {
            y++;
            x = 0;
        }
        board.PlaceShip(static_cast<CellState>(type), Vector2{x,y});
        
        

        x++;
        if(type >= CellState::ELEMENT_COUNT - 1)
            type = CellState::EMPTY;
        else
        type++;
        //y++;
    }*/
    
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for(int i = 0; i < mShips.size(); i++)
            {
                Vector2 pos = mShips[i].mPos;
                CellState type = mShips[i].mCellState;
                if(CheckCollisionPointRec(GetMousePosition(), Rectangle{pos.x,pos.y,44,44}))
                {
                    
                    //mShip1[i] = GetMousePosition();
                    DrawText("Collide!", 10, 10, 50, RED);
                    mCurrShipId = i;
                }
            }

        }
        
    }
    //else
    {
        //for(int i = 0; i < 10; i++)
        //{
        //    if(CheckCollisionPointRec(GetMousePosition(), Rectangle{i * 44 + 100 ,i * 44 + 250,44,44}))
        //        std::cout <<  "Colide!!";
        //}
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for(int x = 0; x < 10; x++)
            for(int y = 0; y < 10; y++)
            {
                if(board.CheckCollision(GetMousePosition(), Vector2{x,y}))
                switch(mShips[mCurrShipId].mCellState)
                {
                    case CellState::BOAT_1:
                        board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x,y});
                        mShips.erase(mShips.begin() + mCurrShipId);
                        mCurrShipId = -1;
                    break;

                    case CellState::BOAT_2:
                        if(x < 9)
                        {
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x,y});
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1,y});
                            mShips.erase(mShips.begin() + mCurrShipId);
                            mCurrShipId = -1;
                        }
                    break;

                    case CellState::BOAT_3:
                        if(x < 8)
                        {
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x,y});
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1,y});
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2,y});
                            mShips.erase(mShips.begin() + mCurrShipId);
                            mCurrShipId = -1;
                        }
                    break;
                    
                    case CellState::BOAT_4:
                        if(x < 7)
                        {
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x,y});
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 1,y});
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 2,y});
                            board.PlaceShip(mShips[mCurrShipId].mCellState, Vector2{x + 3,y});
                            mShips.erase(mShips.begin() + mCurrShipId);
                            mCurrShipId = -1;
                        }
                    break;
                }
                //DrawRectangle(x * 45 + 100, y * 45 + 251,44,44,WHITE);
            }
    }

    if(mCurrShipId != -1)
    {
        //mFollowMouse->x = GetMouseX() - 22;
        //mFollowMouse->y = GetMouseY() - 22;
        Vector2 mousePos = GetMousePosition();
        
        Vector2 &shipPos = mShips[mCurrShipId].mPos; 
        mousePos.x -= 22;
        mousePos.y -= 22;
        
        shipPos = GetSplinePointLinear(mousePos, shipPos, 0.7f);
    }
}



void App::DrawMenu(Button &menuButton)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    
    if(menuButton.IsMouseOverButton())
        menuButton.Draw(DARKBLUE);

    DrawText("Warship Game",GetScreenWidth() / 3.5f, GetScreenHeight() / 3, 50, WHITE);
    DrawText("Play",GetScreenWidth() / 2.f, GetScreenHeight() / 2, 50, WHITE);

    DrawTexture(mCrosshairTexture, GetMouseX() - 10, GetMouseY() - 10,WHITE);

    EndDrawing();
};


void App::MenuInputHandler(Button &menuButton)
{
    if(menuButton.IsButtonPressed(MOUSE_BUTTON_LEFT))
    {
        mShouldDrawMenu = 0;
    }
}

void App::UpdateMenu()
{
    static Button menuButton(Rectangle{GetScreenWidth() / 2.f - 2,GetScreenHeight() / 2.f + 3,109,49});
    MenuInputHandler(menuButton);
    DrawMenu(menuButton);
}
