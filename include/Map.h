#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include "Tile.h"

class Map
{
    public:

        Map() :
            mNumSelected(0),
            mTileSize(0),
            mWidth(0),
            mHeight(0),
            mNumRegions{ {1} }
        {}
        Map(const std::string& filename, unsigned int width, unsigned int height,
        std::map<std::string, Tile>const& tileAtlas) :
            mTiles(),
            mTileSize(8),
            mNumSelected(0)
        {
            load(filename, width, height, tileAtlas);
        }


    public:

        void draw(sf::RenderWindow& window, float dt);

    public:

        void select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist);
        void clearSelected();

    public:

        void findConnectedRegions(std::vector<TileType> whitelist, int type);
        void updateDirection(TileType tileType);

    public:

        void load(std::string const& filepath, unsigned int width, unsigned int height, std::map<std::string, Tile>const& tileAtlas);
        void save(std::string const& filepath);

    public:

        std::vector<Tile> mTiles;

        unsigned int mWidth;
        unsigned int mHeight;

    public:

        std::vector<char> mSelected; // 0 = No, 1 = Yes, 2 = Invalid
        unsigned int mNumSelected;

    public:

        std::vector<int> mResources;

        unsigned int mTileSize;
        unsigned int mNumRegions[1];

    private:

        void depthFirstSearch(std::vector<TileType>& whiteList, sf::Vector2i pos, int label, int type);
};

#endif // MAP_H
