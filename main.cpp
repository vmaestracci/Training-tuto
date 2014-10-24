
#include "Game.h"

#include "GameStateStart.h"

#include <ctime>

/*
SOMETHING WRONG IN MAP
*/

int main()
{
    srand(time(0));

    Game game;

    game.pushState(new GameStateStart(&game));
    game.gameLoop();

    return 0;
}
