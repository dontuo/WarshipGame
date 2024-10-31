#include "board.hpp"
#include "button.hpp"
#include "cell.hpp"
#include "global.hpp"
#include "grid.hpp"
#include "player.hpp"
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

    void Run();

  private:
    void UpdateGame();
    void DrawGame();
    void GameInputHandler();

    void UpdateMenu();
    void DrawMenu(Button &menuButton);
    void MenuInputHandler(Button &menuButton);

    void InitShips();

    bool mShouldDrawMenu = 1;

    Texture2D mCrosshairTexture;

    // current cell id depend on cursor
    Vector2 mCurrCursorCell = {-1, -1};

    std::vector<Player> mPlayers{};

    Player *mCurrPlayer;
};
