#include "board.h"
#include "cell.h"
#include "grid.h"
#include "raylib.h"
#include <vector>


Board::Board(int offsetX, int offsetY)
    :mOffset{Vector2{(float)offsetX,(float)offsetY}}
{
    mTextures[CellState::EMPTY] = LoadTexture("textures/empty.png"); 
    mTextures[CellState::BOAT_1] = LoadTexture("textures/ship_1.png"); 
    mTextures[CellState::BOAT_2] = LoadTexture("textures/ship_2.png"); 
    mTextures[CellState::BOAT_3] = LoadTexture("textures/ship_3.png"); 
    mTextures[CellState::BOAT_4] = LoadTexture("textures/ship_4.png"); 
    mTextures[CellState::BOAT_1_HITTED] = LoadTexture("textures/ship_1_hitted.png"); 
    mTextures[CellState::BOAT_2_HITTED] = LoadTexture("textures/ship_2_hitted.png"); 
    mTextures[CellState::BOAT_3_HITTED] = LoadTexture("textures/ship_3_hitted.png"); 
    mTextures[CellState::BOAT_4_HITTED] = LoadTexture("textures/ship_4_hitted.png"); 
    mTextures[CellState::HIT] = LoadTexture("textures/hit.png"); 
    mTextures[CellState::MISSED] = LoadTexture("textures/miss.png"); 
}


Board::Board(Vector2 offset)
    :mOffset(offset)
{
    mTextures[CellState::EMPTY] = LoadTexture("textures/empty.png"); 
    mTextures[CellState::BOAT_1] = LoadTexture("textures/ship_1.png"); 
    mTextures[CellState::BOAT_2] = LoadTexture("textures/ship_2.png"); 
    mTextures[CellState::BOAT_3] = LoadTexture("textures/ship_3.png"); 
    mTextures[CellState::BOAT_4] = LoadTexture("textures/ship_4.png"); 
    mTextures[CellState::BOAT_1_HITTED] = LoadTexture("textures/ship_1_hitted.png"); 
    mTextures[CellState::BOAT_2_HITTED] = LoadTexture("textures/ship_2_hitted.png"); 
    mTextures[CellState::BOAT_3_HITTED] = LoadTexture("textures/ship_3_hitted.png"); 
    mTextures[CellState::BOAT_4_HITTED] = LoadTexture("textures/ship_4_hitted.png"); 
    mTextures[CellState::HIT] = LoadTexture("textures/hit.png"); 
    mTextures[CellState::MISSED] = LoadTexture("textures/miss.png");
}


void Board::Draw(bool Hide)
{
    DrawGrid(10,10, 45,mOffset.x, mOffset.y, BLACK);

    if(Hide)
    {
        for(int x = 0; x < 10; x++)
            for(int y = 0; y < 10; y++)
            {
                //DrawRectangle(mOffset.x + (44 * x), mOffset.y + (44 * y) + 1, 44, 44, Color{(x/10.f) * 255, (y/10.f) * 255,255,255});
                //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, Color{(x/10.f) * 255, (y/10.f) * 255,255,255});
                switch (mCells[x][y]) 
                {
                    
                    case CellState::EMPTY:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, BLACK);
                        DrawTexture(mTextures[CellState::EMPTY],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::BOAT_1_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_1_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                    
                    case CellState::BOAT_2_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_2_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                
                    case CellState::BOAT_3_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_3_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::BOAT_4_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_4_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::MISSED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::MISSED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::HIT:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::HIT],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    default:
                        DrawTexture(mTextures[CellState::EMPTY],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, WHITE);
                    break;
                }
            }
    }
    else
    {
        for(int x = 0; x < 10; x++)
            for(int y = 0; y < 10; y++)
            {
                switch (mCells[x][y]) 
                {
                    
                    case CellState::EMPTY:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, BLACK);
                        DrawTexture(mTextures[CellState::EMPTY],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::BOAT_1:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_1],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::BOAT_2:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_2],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::BOAT_3:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_3],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::BOAT_4:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_4],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                    
                    case CellState::BOAT_1_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_1_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                    
                    case CellState::BOAT_2_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_2_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                
                    case CellState::BOAT_3_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_3_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::BOAT_4_HITTED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::BOAT_4_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::MISSED:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::MISSED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::HIT:
                        //DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, RED);
                        DrawTexture(mTextures[CellState::HIT],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    default:
                        DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, WHITE);
                    break;
                }


            }  
    }
}

bool Board::PlaceShip(CellState type, Vector2 position)
{
    bool result = 1;
    
    mCells[(int)position.x][(int)position.y] = type;
    
    return result;
}

bool CheckHit()
{
    bool result = 0;
    
    return result;
}


void Board::PrintCells()
{

    std::cout << "--------------------" << '\n';
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
            std::cout << mCells[x][y] << '|';

        std::cout << '\n';
    }

}

bool Board::CheckCollision(Vector2 pos, Vector2 cell)
{
    return (CheckCollisionPointRec(pos,Rectangle{cell.x * 45 + mOffset.x, cell.y * 45 + mOffset.y, 44, 44}));
}
