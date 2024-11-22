#include "board.hpp"
#include "cell.hpp"
#include "global.hpp"
#include "raymath.h"
#include "ship.hpp"
#include <raylib.h>
#include <string>
#include <vector>

class Player : public Board
{
  public:
    Player(std::string name);

    // draws board and ships
    void Draw(int offsetX, int offsetY, bool hide);

    void InitShips();

    std::string mName;
    std::vector<Ship> mShips;

    void HandleShipPlacement(int x, int y);
    void HandleShipSelection();

    void UpdateCurrShip();

    int mCurrShipId = -1;
};
