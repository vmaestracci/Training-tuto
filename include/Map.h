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

        Map() {}
        Map(const std::string& filename, unsigned int width, unsigned int height,
        std::map<std::string, Tile>const& tileAtlas) :
            mTiles(),
            mTileSize(8)
        {
            load(filename, width, height, tileAtlas);
        }


    public:

        void draw(sf::RenderWindow& window, float dt);

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

        std::vector<int> mResources;

        unsigned int mTileSize;
        unsigned int mNumSelected;
        unsigned int mNumRegions[1];

    private:

        void depthFirstSearch(std::vector<TileType>& whiteList, sf::Vector2i pos, int label, int type);
};

#endif // MAP_H
