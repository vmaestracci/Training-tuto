#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"

class Game;

class GameState
{
    public:

        Game* mGame;

        virtual void draw(const float dt) = 0;
        virtual void update(const float dt) = 0;
        virtual void handleInput() = 0;
};

#endif // GAMESTATE_H
