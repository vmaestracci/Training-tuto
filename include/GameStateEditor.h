#ifndef GAMESTATEEDITOR_H
#define GAMESTATEEDITOR_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>*

#include "GameState.h"

#include "Map.h"

enum class ActionState { NONE, PANNING, SELECTING };

class GameStateEditor : public GameState
{
    public:
        GameStateEditor(Game* game);

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

    private:
        Map mMap;

        sf::Vector2i mSelectionStart;
        sf::Vector2i mSelectionEnd;
        Tile* mCurrentTile;

    private:
        sf::View mGameView;
        sf::View mGuiView;

    private:
        ActionState mActionState;
        sf::Vector2i mPanningAnchor;
        float mZoomLevel;

};

#endif // GAMESTATEEDITOR_H
