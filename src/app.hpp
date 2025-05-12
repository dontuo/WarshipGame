#include "board.hpp"
#include "button.hpp"
#include "cell.hpp"
#include "gamestate.hpp"
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
    ~App();

    void Run();

  private:
    // main menu
    void UpdateMenu();
    void DrawMenu();
    void MenuInputHandler();

    // placing ships
    void UpdateShipPlacement();
    void DrawShipPlacement();
    void ShipPlacementInputHandler();

    // game
    void UpdateGame();
    void DrawGame();
    void GameInputHandler();

    // end menu
    void UpdateEndGame();
    void DrawEndGame();
    void EndGameInputHandler();

    void processHits();

    bool IsPlayerDefeated(Player &player);
    void InitShips();

    void UpdateClay();

    Texture2D mCrosshairTexture;
    Texture2D mBackgroundTexture;

    std::vector<Player> mPlayers{};

    Player *mCurrPlayer;
    Font mFonts[1];

    // 0 - first player, 1 - second player
    bool mCurrPlayerTurn = 1;
};
