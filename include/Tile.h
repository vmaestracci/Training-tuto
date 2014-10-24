#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "AnimationHandler.h"

enum class TileType { VOID, GRASS, FOREST, WATER, RESIDENTIAL, COMMERCIAL, INDUSTRIAL, ROAD };

std::string tileTypeToStr(TileType type);

class Tile
{
    public:

        Tile() {}

        Tile(const unsigned int tileSize, const unsigned int height, sf::Texture& texture,
        const std::vector<Animation>& animations,
        const TileType tileType, const unsigned int cost, const unsigned int maxPopPerLevel,
        const unsigned int maxLevels) :
            mTileType(tileType),
            mMaxPopPerLevel(maxPopPerLevel),
            mMaxLevels(maxLevels),
            mTileVariant(0),
            mCost(cost),
            mPopulation(0),
            mSprite(),
            mAnimHandler()
         {
            mRegions[0] = 0;

            mSprite.setOrigin(sf::Vector2f(0.0f,tileSize*(height-1)));
            mSprite.setTexture(texture);

            mAnimHandler.mFrameSize = sf::IntRect(0, 0, tileSize*2, tileSize*height);
            for(auto a : animations)
                mAnimHandler.addAnim(a);
            mAnimHandler.update(0.0f);
         }

    public:

        void draw(sf::RenderWindow& window, const float dt);
        void update();

        std::string getCost() { return std::to_string(mCost); }

    public:

        AnimationHandler mAnimHandler;
        sf::Sprite mSprite;

        TileType mTileType;
        int mTileVariant;

        unsigned int mRegions[1];

        unsigned int mCost;

        double mPopulation;

        unsigned int mMaxPopPerLevel;

        unsigned int mMaxLevels;

        float mProduction;

        float mStoredGoods;
};

#endif // TILE_H
