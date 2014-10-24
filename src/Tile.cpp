#include "Tile.h"

#include <SFML/Graphics.hpp>

#include "AnimationHandler.h"

void Tile::draw(sf::RenderWindow& window, const float dt)
{
    mAnimHandler.changeAnim(mTileVariant);

    mAnimHandler.update(dt);

    mSprite.setTextureRect(mAnimHandler.mBounds);

    window.draw(mSprite);
}

void Tile::update()
{
    if((mTileType == TileType::RESIDENTIAL || mTileType == TileType::COMMERCIAL || mTileType == TileType::INDUSTRIAL)
       && mPopulation == mMaxPopPerLevel * (mTileVariant+1)
       && mTileVariant < mMaxLevels)
       if(rand() % static_cast<int>(1e4) < static_cast<int>(1e2)/(mTileVariant+1)) // Une petite chance pour que
            ++mTileVariant; // On passe au niveau superieur
}

std::string tileTypeToStr(TileType type)
{
    switch(type)
    {
        default:
        case TileType::VOID:            return "Vide";
        case TileType::GRASS:           return "Terrain Plat";
        case TileType::FOREST:          return "Foret";
        case TileType::WATER:           return "Eau";
        case TileType::RESIDENTIAL:     return "Zone Residentielle";
        case TileType::COMMERCIAL:      return "Zone Commerciale";
        case TileType::INDUSTRIAL:      return "Zone Industrielle";
    }
}
