#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>
#include <map>
#include <string>

#include "GameState.h"

#include "TextureManager.h"
#include "Tile.h"

class GameState;

class Game
{
     public:

         Game();
        ~Game();

    public:

        void pushState(GameState* state);
        void popState();
        void changeState(GameState* state);

        GameState* peekState();

        void gameLoop();

    public:

        std::stack<GameState*> mStates;
        sf::RenderWindow mWindow;

    public:

        TextureManager mTexMgr;
        std::map<std::string, Tile> mTileAtlas;

    public:

        const static int tileSize = 8;
        sf::Sprite mBackground;

    private:

        void loadTextures();
        void loadTiles();
};

#endif // GAME_H
