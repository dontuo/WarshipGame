#include "board.h"

Board::Board(int offsetX, int offsetY)
    :mOffset{Vector2{(float)offsetX,(float)offsetY}}
{}


Board::Board(Vector2 offset)
    :mOffset(offset)
{}

void Board::Draw(bool Hide)
{
    DrawGrid(10,10, 45,mOffset.x, mOffset.y, BLACK);

    if(Hide)
    {
        for(int x = 0; x < 10; x++)
        {
            for(int y = 0; y < 10; y++)
            {
                switch (mCells[x][y]) 
                {
                    
                    case CellState::EMPTY:
                        DrawTexture(textures[CellState::EMPTY],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::SHIP_1_HITTED:
                        DrawTexture(textures[CellState::SHIP_1_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                    
                    case CellState::SHIP_2_HITTED:
                        DrawTexture(textures[CellState::SHIP_2_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                
                    case CellState::SHIP_3_HITTED:
                        DrawTexture(textures[CellState::SHIP_3_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::SHIP_4_HITTED:
                        DrawTexture(textures[CellState::SHIP_4_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::MISSED:
                        DrawTexture(textures[CellState::MISSED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::HIT:
                        DrawTexture(textures[CellState::HIT],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    default:
                        DrawTexture(textures[CellState::EMPTY],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                }
            }
        }
    }
    else
    {
        for(int x = 0; x < 10; x++)
        {
            for(int y = 0; y < 10; y++)
            {
                switch (mCells[x][y]) 
                {
                    case CellState::EMPTY:
                        DrawTexture(textures[CellState::EMPTY],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::SHIP_1:
                        DrawTexture(textures[CellState::SHIP_1],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::SHIP_2:
                        DrawTexture(textures[CellState::SHIP_2],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::SHIP_3:
                        DrawTexture(textures[CellState::SHIP_3],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::SHIP_4:
                        DrawTexture(textures[CellState::SHIP_4],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                    
                    case CellState::SHIP_1_HITTED:
                        DrawTexture(textures[CellState::SHIP_1_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                    
                    case CellState::SHIP_2_HITTED:
                        DrawTexture(textures[CellState::SHIP_2_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;
                
                    case CellState::SHIP_3_HITTED:
                        DrawTexture(textures[CellState::SHIP_3_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::SHIP_4_HITTED:
                        DrawTexture(textures[CellState::SHIP_4_HITTED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::MISSED:
                        DrawTexture(textures[CellState::MISSED],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    case CellState::HIT:
                        DrawTexture(textures[CellState::HIT],mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, WHITE);
                    break;

                    default:
                        DrawRectangle(mOffset.x + (45 * x), mOffset.y + (45 * y) + 1, 44, 44, WHITE);
                    break;
                }
            }
        }
    }
}

bool Board::PlaceShip(CellState type, Vector2 position)
{
    // for future (check if something already on this cell)
    bool result = 1;
    
    mCells[(int)position.x][(int)position.y] = type;
    
    return result;
}

bool CheckHit()
{
    // yeah... In the future
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


CellState Board::GetCellState(int x, int y)
{
    return mCells[x][y];
}

CellState Board::GetCellState(Vector2 pos)
{
    return mCells[pos.x][pos.y];
}
