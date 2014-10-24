#ifndef GAMESTATEEDITOR_H
#define GAMESTATEEDITOR_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>*

#include "GameState.h"

#include "Map.h"

enum class ActionState { NONE, PANNING };

class GameStateEditor : public GameState
{
    public:
        GameStateEditor(Game* game);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

    private:
        Map mMap;

        sf::View mGameView;
        sf::View mGuiView;

    private:
        ActionState mActionState;
        sf::Vector2i mPanningAnchor;
        float mZoomLevel;

};

#endif // GAMESTATEEDITOR_H
