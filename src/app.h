#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <stdexcept>
#include <math.h>
#include <vector>
#include "button.h"
#include "grid.h"
#include "board.h"
#include "ship.h"
#include "cell.h"



class App
{
public:
    App();
    void Init();

    void Run();

private:
    void GameDraw(Board &board);
    void UpdateGame();
    void GameInputHandler(Board &board);
    
    void UpdateMenu();
    void DrawMenu(Button &menuButton);
    void MenuInputHandler(Button &menuButton);

private:
    bool mShouldDrawMenu = 0;
    
    Texture2D mCrosshairTexture;
        
    std::vector<Ship> mShips{4 + 3 + 2 + 1};
    
    int mCurrShipId = -1;

     

    int mWindowWidth = 1280;
    int mWindowHeight = 720;

};
