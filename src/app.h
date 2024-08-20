#include <raylib.h>
#include <iostream>
#include <stdexcept>
#include <math.h>


class App
{
public:
    App();
    void Init();

    void Run();

    void Draw();

    void DrawMenu();
private:
    bool ShouldDrawMenu = 0; 
};
