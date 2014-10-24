#include "GameStateEditor.h"

#include "GameStateStart.h"
#include "GameState.h"

GameStateEditor::GameStateEditor(Game* game) :
    mGameView(),
    mGuiView(),
    mZoomLevel(0.1f),
    mActionState(ActionState::NONE)
{
    mGame = game;

    sf::Vector2f size = static_cast<sf::Vector2f>(mGame->mWindow.getSize());

    mGameView.setSize(size);
    mGuiView.setSize(size);
    size *= 0.5f; //On divise par 2
    mGameView.setCenter(size);
    mGuiView.setCenter(size);

    mMap = Map("city_map.dat", 64, 64, mGame->mTileAtlas);

    sf::Vector2f centre(mMap.mWidth, mMap.mHeight*0.5);
    centre *= static_cast<float>(mMap.mTileSize);
    mGameView.setCenter(centre);
}

void GameStateEditor::draw(const float dt)
{
    mGame->mWindow.clear(sf::Color::Black);

    mGame->mWindow.setView(mGuiView);
    mGame->mWindow.draw(mGame->mBackground);

    mGame->mWindow.setView(mGameView);
    mMap.draw(mGame->mWindow, dt);
}

void GameStateEditor::update(const float dt)
{
}

void GameStateEditor::handleInput()
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
                mGameView.setSize(event.size.width, event.size.height);
                mGameView.zoom(mZoomLevel);
                mGuiView.setSize(event.size.width, event.size.height);
                mGame->mBackground.setPosition(mGame->mWindow.mapPixelToCoords(sf::Vector2i(0,0), mGuiView));
                mGame->mBackground.setScale(
                static_cast<float>(event.size.width)/static_cast<float>(mGame->mBackground.getTexture()->getSize().x),
                static_cast<float>(event.size.height)/static_cast<float>(mGame->mBackground.getTexture()->getSize().y)
                                            );
            }
            break;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
                mGame->mWindow.close();
            break;

        case sf::Event::MouseMoved:
            {
                if(mActionState == ActionState::PANNING)
                {
                    sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mGame->mWindow) - mPanningAnchor);
                    mGameView.move(-1.0f * pos * mZoomLevel);
                    mPanningAnchor = sf::Mouse::getPosition(mGame->mWindow);
                }
            }
            break;

        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Middle)
                if(mActionState != ActionState::PANNING)
                {
                    mActionState = ActionState::PANNING;
                    mPanningAnchor = sf::Mouse::getPosition(mGame->mWindow);
                }
            break;

        case sf::Event::MouseButtonReleased:
            if(event.mouseButton.button == sf::Mouse::Middle)
                mActionState = ActionState::NONE;
            break;

        case sf::Event::MouseWheelMoved:
            if(event.mouseWheel.delta < 0)
            {
                mGameView.zoom(2.0f);
                mZoomLevel *= 2.0f;
            }
            else
            {
                mGameView.zoom(0.5f);
                mZoomLevel *= 0.5f;
            }
            break;
        }
    }
}
