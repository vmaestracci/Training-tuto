#ifndef GAMESTATESTART_H
#define GAMESTATESTART_H

#include <SFML/Graphics.hpp>

#include "GameState.h"

class GameStateStart : public GameState
{
    public:
        GameStateStart(Game* game);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

    private:
        sf::View mView;

    private:
        void loadGame(); // Transition between states
};

#endif // GAMESTATESTART_H
