#include "GameStateStart.h"

#include "GameStateEditor.h"
#include "GameState.h"

/*
mGame = game;

    sf::Vector2f size = static_cast<sf::Vector2f>(mGame->mWindow.getSize());
    mView.setSize(size);
    size *= 0.5f; //On divise par 2
    mView.setCenter(size);
*/

GameStateStart::GameStateStart(Game* game) : mView()
{
    mGame = game;

    sf::Vector2f size = static_cast<sf::Vector2f>(mGame->mWindow.getSize());
    mView.setSize(size);
    size *= 0.5f; //On divise par 2
    mView.setCenter(size);
}

void GameStateStart::draw(const float dt)
{
    mGame->mWindow.setView(mView);
    mGame->mWindow.clear(sf::Color::Black);
    mGame->mWindow.draw(mGame->mBackground);
}

void GameStateStart::update(const float dt)
{
    //Nothing here
}

void GameStateStart::handleInput()
{
    sf::Event event;

    while(mGame->mWindow.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            mGame->mWindow.close();
            break;

        case sf::Event::Resized:
            {
                mView.setSize(event.size.width, event.size.height);
                mGame->mBackground.setPosition(mGame->mWindow.mapPixelToCoords(sf::Vector2i(0,0), mView));
                mGame->mBackground.setScale(
                static_cast<float>(event.size.width)/static_cast<float>(mGame->mBackground.getTexture()->getSize().x),
                static_cast<float>(event.size.height)/static_cast<float>(mGame->mBackground.getTexture()->getSize().y)
                                            );
            }
            break;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
                mGame->mWindow.close();
            else if(event.key.code == sf::Keyboard::Space)
                loadGame();
            break;
        }
    }
}

void GameStateStart::loadGame()
{
    mGame->pushState(new GameStateEditor(mGame));
}
