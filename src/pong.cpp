#include "game.h"

int main(int argc, char* argv[])
{
    const int screen_height{300};
    const int screen_width{600};

    Game game{screen_height, screen_width};
    game.run();
    
    return 0;
}