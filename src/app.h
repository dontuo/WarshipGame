#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <stdexcept>
#include <math.h>
#include "button.h"


class App
{
public:
    App();
    void Init();

    void Run();

    void Draw();

    void DrawMenu();
private:
    bool mShouldDrawMenu = 0;
    
    Texture2D mCrosshairTexture;
    Texture2D mShip1Texture;
    int mWindowWidth = 1280;
    int mWindowHeight = 720;
};
