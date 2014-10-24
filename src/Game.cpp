#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GameState.h"

#include "TextureManager.h"

Game::Game() : mWindow(sf::VideoMode(800, 600), "City Builder")
{
    loadTextures();
    loadTiles();

    mWindow.setFramerateLimit(60); // 60 fps max

    mBackground.setTexture(mTexMgr.getRef("background"));
}

void Game::pushState(GameState* state)
{
    mStates.push(state);
}

void Game::popState()
{
    delete mStates.top();
    mStates.pop();
}

void Game::changeState(GameState* state)
{
    if(!mStates.empty())
        popState();
    pushState(state);
}

GameState* Game::peekState()
{
    if(mStates.empty()) return nullptr;
    return mStates.top();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(mWindow.isOpen())
    {
        float time = clock.restart().asSeconds();

        if(peekState() == nullptr) // No state
            continue; // Let's redo the gameLoop

        peekState()->handleInput();

        peekState()->update(time);

        mWindow.clear(sf::Color::Black);
        peekState()->draw(time);
        mWindow.display();
    }
}

void Game::loadTextures()
{
    mTexMgr.loadTexture("grass",         "media/grass.png");
    mTexMgr.loadTexture("forest",        "media/forest.png");
    mTexMgr.loadTexture("water",         "media/water.png");
    mTexMgr.loadTexture("residential",   "media/residential.png");
    mTexMgr.loadTexture("commercial",    "media/commercial.png");
    mTexMgr.loadTexture("industrial",    "media/industrial.png");
    mTexMgr.loadTexture("road",          "media/road.png");

    mTexMgr.loadTexture("background",      "media/background.png");
}

void Game::loadTiles()
{
    Animation staticAnim(0, 0, 1.0f);
    mTileAtlas["grass"] =
        Tile(Game::tileSize, 1, mTexMgr.getRef("grass"),
            { staticAnim },
            TileType::GRASS, 50, 0, 1);
    mTileAtlas["forest"] =
        Tile(Game::tileSize, 1, mTexMgr.getRef("forest"),
            { staticAnim },
            TileType::FOREST, 100, 0, 1);
    mTileAtlas["water"] =
        Tile(Game::tileSize, 1, mTexMgr.getRef("water"),
            { Animation(0, 3, 0.5f),
            Animation(0, 3, 0.5f),
            Animation(0, 3, 0.5f) },
            TileType::WATER, 0, 0, 1);
    mTileAtlas["residential"] =
        Tile(Game::tileSize, 2, mTexMgr.getRef("residential"),
            { staticAnim, staticAnim, staticAnim,
            staticAnim, staticAnim, staticAnim },
            TileType::RESIDENTIAL, 300, 50, 6);
    mTileAtlas["commercial"] =
        Tile(Game::tileSize, 2, mTexMgr.getRef("commercial"),
            { staticAnim, staticAnim, staticAnim, staticAnim},
            TileType::COMMERCIAL, 300, 50, 4);
    mTileAtlas["industrial"] =
        Tile(Game::tileSize, 2, mTexMgr.getRef("industrial"),
            { staticAnim, staticAnim, staticAnim,
            staticAnim },
            TileType::INDUSTRIAL, 300, 50, 4);
    mTileAtlas["road"] =
        Tile(Game::tileSize, 1, mTexMgr.getRef("road"),
            { staticAnim, staticAnim, staticAnim,
            staticAnim, staticAnim, staticAnim,
            staticAnim, staticAnim, staticAnim,
            staticAnim, staticAnim },
            TileType::ROAD, 100, 0, 1);
}

Game::~Game()
{
    while(!mStates.empty()) popState();
}

