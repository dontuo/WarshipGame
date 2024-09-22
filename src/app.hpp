#include "board.hpp"
#include "button.hpp"
#include "cell.hpp"
#include "grid.hpp"
#include "ship.hpp"
#include <iostream>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdexcept>
#include <vector>

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
    void InitShips();

    bool mShouldDrawMenu = 0;

    Texture2D mCrosshairTexture;
    // storing what type of ship and their coordinates
    std::vector<Ship> mShips{4 + 3 + 2 + 1};

    int mCurrShipId = -1;

    // current cell id depend on cursor
    Vector2 mCurrCursorCell = {-1, -1};

    int mWindowWidth = 1280;
    int mWindowHeight = 720;
};
