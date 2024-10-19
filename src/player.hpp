#include "board.hpp"
#include "cell.hpp"
#include "raymath.h"
#include "ship.hpp"
#include "global.hpp"
#include <string>
#include <vector>
#include <raylib.h>


class Player : public Board
{
  public:
    Player(std::string name);

    // draws board and ships
    void Draw(int offsetX, int offsetY, bool hide);

    void InitShips();

    std::string mName;
    std::vector<Ship> mShips;
    

    bool HandleShipPlacement(int x, int y);
    void HandleShipSelection();

    void UpdateCurrShipPosition();

    int mCurrShipId = -1;
};
