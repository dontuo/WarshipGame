#include "app.h"

int main()
{

    App app;
    try
    {
        app.Init();
        app.Run();
    }
    catch(std::runtime_error &e) 
    {
        std::cout << "error:" << e.what() << '\n';
        return -1;
    }
 
    return 0;
}
