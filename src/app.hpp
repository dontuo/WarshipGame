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

    void Run();

  private:
    // main menu
    void UpdateMenu();
    void DrawMenu(Button &menuButton);
    void MenuInputHandler(Button &menuButton);

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

    bool IsPlayerDefeated(Player& player);
    void InitShips();
    
    Texture2D mCrosshairTexture;

    std::vector<Player> mPlayers{};

    Player *mCurrPlayer;

    // 0 - first player, 1 - second player
    bool mCurrPlayerTurn = 1;
};
