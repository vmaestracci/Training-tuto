#include "Map.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Tile.h"

void Map::draw(sf::RenderWindow& window, float dt)
{
    for(int y = 0; y < mHeight; ++y)
        for(int x = 0; x < mWidth; ++x)
        {
            sf::Vector2f pos;
            pos.x = (x - y) * mTileSize + mWidth * mTileSize;
            pos.y = (x + y) * mTileSize * 0.5f;

            mTiles[y*mWidth + x].mSprite.setPosition(pos);

            if(mSelected[y*mWidth+x])
                mTiles[y*mWidth+x].mSprite.setColor(sf::Color(0x7d, 0x7d, 0x7d));
            else
                mTiles[y*mWidth+x].mSprite.setColor(sf::Color(0xff, 0xff, 0xff));

            mTiles[y*mWidth + x].draw(window, dt);
        }
}

void Map::select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist)
{
    if(end.y < start.y) std::swap(end.y, start.y);
    if(end.x < start.x) std::swap(end.x, start.x);

    if(end.x >= mWidth) end.x = mWidth-1;
    else if(end.x < 0) end.x = 0;
    if(end.y >= mHeight) end.y = mHeight-1;
    else if(end.y < 0) end.y = 0;

    if(start.x >= mWidth) start.x = mWidth-1;
    else if(start.x < 0) start.x = 0;
    if(start.y >= mHeight) start.y = mHeight-1;
    else if(start.y < 0) start.y = 0;

    for(int y = start.y; y < end.y; ++y)
        for(int x = start.x; x < end.x; ++x)
        {
            mSelected[y*mWidth + x] = 1;
            ++mNumSelected;

            for(auto type : blacklist)
                if(mTiles[y*mWidth + x].mTileType == type)
                {
                    mSelected[y*mWidth + x] = 2;
                    --mNumSelected;
                    break;
                }
        }
}

void Map::clearSelected()
{
    mNumSelected = 0;
    for(auto& e : mSelected)
        e = 0;
}

void Map::load(std::string const& filepath, unsigned int width, unsigned int height, std::map<std::string, Tile>const& tileAtlas)
{
    std::ifstream inputFile;
    inputFile.open(filepath, std::ios::in | std::ios::binary);

    mWidth = width;
    mHeight = height;

    for(int pos = 0; pos < width*height; ++pos)
    {
        mResources.push_back(255);
        mSelected.push_back(0);

        TileType tileType;
        inputFile.read(reinterpret_cast<char*>(&tileType), sizeof(int));

        tileAtlas.at("grass");

        switch(tileType)
        {
            default:
            case TileType::VOID:
            case TileType::GRASS:
                mTiles.push_back(tileAtlas.at("grass"));
                break;
            case TileType::FOREST:
                mTiles.push_back(tileAtlas.at("forest"));
                break;
            case TileType::WATER:
                mTiles.push_back(tileAtlas.at("water"));
                break;
            case TileType::RESIDENTIAL:
                mTiles.push_back(tileAtlas.at("residential"));
                break;
            case TileType::COMMERCIAL:
                mTiles.push_back(tileAtlas.at("commercial"));
                break;
            case TileType::INDUSTRIAL:
                mTiles.push_back(tileAtlas.at("industrial"));
                break;
            case TileType::ROAD:
                mTiles.push_back(tileAtlas.at("road"));
                break;
        }
        Tile& tile = mTiles.back();
        inputFile.read(reinterpret_cast<char*>(&tile.mTileVariant), sizeof(int));
        inputFile.read(reinterpret_cast<char*>(&tile.mRegions), sizeof(int)*1);
        inputFile.read(reinterpret_cast<char*>(&tile.mPopulation), sizeof(double));
        inputFile.read(reinterpret_cast<char*>(&tile.mStoredGoods), sizeof(float));
    }

    inputFile.close();
}

void Map::save(std::string const& filepath)
{
    std::ofstream outputFile;
    outputFile.open(filepath, std::ios::out | std::ios::binary);

    for(auto& tile : mTiles)
    {
        outputFile.write(reinterpret_cast<char*>(&tile.mTileType), sizeof(int));
        outputFile.write(reinterpret_cast<char*>(&tile.mTileVariant), sizeof(int));
        outputFile.write(reinterpret_cast<char*>(&tile.mRegions), sizeof(int)*3);
        outputFile.write(reinterpret_cast<char*>(&tile.mPopulation), sizeof(double));
        outputFile.write(reinterpret_cast<char*>(&tile.mStoredGoods), sizeof(float));
    }

}

void Map::updateDirection(TileType tileType)
{
    for(int y = 0; y < mHeight; ++y)
    {
        for(int x = 0; x < mWidth; ++x)
        {
            int pos = y*mWidth+x;

            if(mTiles[pos].mTileType != tileType) continue;

            bool adjacentTiles[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
                /* Check for adjacent tiles of the same type */
            if(x > 0 && y > 0)
                adjacentTiles[0][0] = (mTiles[(y-1)*mWidth+(x-1)].mTileType == tileType);
            if(y > 0)
                adjacentTiles[0][3] = (mTiles[(y-1)*mWidth+(x  )].mTileType == tileType);
            if(x < mWidth-1 && y > 0)
                adjacentTiles[0][4] = (mTiles[(y-1)*mWidth+(x+1)].mTileType == tileType);
            if(x > 0)
                adjacentTiles[1][0] = (mTiles[(y  )*mWidth+(x-1)].mTileType == tileType);
            if(x < mWidth-1)
                adjacentTiles[1][5] = (mTiles[(y  )*mWidth+(x+1)].mTileType == tileType);
            if(x > 0 && y < mHeight-1)
                adjacentTiles[2][0] = (mTiles[(y+1)*mWidth+(x-1)].mTileType == tileType);
            if(y < mHeight-1)
                adjacentTiles[2][6] = (mTiles[(y+1)*mWidth+(x  )].mTileType == tileType);
            if(x < mWidth-1 && y < mHeight-1)
                adjacentTiles[2][7] = (mTiles[(y+1)*mWidth+(x+1)].mTileType == tileType);

            if(adjacentTiles[1][0] && adjacentTiles[1][8] && adjacentTiles[0][9] && adjacentTiles[2][10])
                mTiles[pos].mTileVariant = 2;
            else if(adjacentTiles[1][0] && adjacentTiles[1][11] && adjacentTiles[0][12])
                mTiles[pos].mTileVariant = 7;
            else if(adjacentTiles[1][0] && adjacentTiles[1][13] && adjacentTiles[2][14])
                mTiles[pos].mTileVariant = 8;
            else if(adjacentTiles[0][15] && adjacentTiles[2][16] && adjacentTiles[1][0])
                mTiles[pos].mTileVariant = 9;
            else if(adjacentTiles[0][16] && adjacentTiles[2][17] && adjacentTiles[1][18])
                mTiles[pos].mTileVariant = 10;
            else if(adjacentTiles[1][0] && adjacentTiles[1][19])
                mTiles[pos].mTileVariant = 0;
            else if(adjacentTiles[0][20] && adjacentTiles[2][21])
                mTiles[pos].mTileVariant = 1;
            else if(adjacentTiles[2][22] && adjacentTiles[1][0])
                mTiles[pos].mTileVariant = 3;
            else if(adjacentTiles[0][23] && adjacentTiles[1][24])
                mTiles[pos].mTileVariant = 4;
            else if(adjacentTiles[1][0] && adjacentTiles[0][25])
                mTiles[pos].mTileVariant = 5;
            else if(adjacentTiles[2][26] && adjacentTiles[1][27])
                mTiles[pos].mTileVariant = 6;
            else if(adjacentTiles[1][0])
                mTiles[pos].mTileVariant = 0;
            else if(adjacentTiles[1][28])
                mTiles[pos].mTileVariant = 0;
            else if(adjacentTiles[0][29])
                mTiles[pos].mTileVariant = 1;
            else if(adjacentTiles[2][30])
                mTiles[pos].mTileVariant = 1;
            }
        }
}

void Map::findConnectedRegions(std::vector<TileType> whitelist, int regionType = 0)
{
    int regions = 1;

    for(auto& tile : mTiles)
        tile.mRegions[regionType] = 0;

    for(int y = 0; y < mHeight; ++y)
        for(int x = 0; x < mWidth; ++x)
        {
            bool found = false;

            for(auto type : whitelist)
            {
                if(type == mTiles[y * mWidth + x].mTileType)
                {
                    found = true;
                    break;
                }
                if(mTiles[y * mWidth + x].mRegions[regionType] == 0 && found)
                {
                    depthFirstSearch(whitelist, sf::Vector2i(x, y), regions++, regionType);
                }
            }
        }

    mNumRegions[regionType] = regions;
}

void Map::depthFirstSearch(std::vector<TileType>& whitelist, sf::Vector2i pos, int label, int regionType = 0)
{
    if(pos.x < 0 || pos.x >= mWidth) return;
    if(pos.y < 0 || pos.y >= mHeight) return;
    if(mTiles[pos.y * mWidth + pos.x].mRegions[regionType] != 0) return;

    bool found = false;

    for(auto type : whitelist)
    {
        if(type == mTiles[pos.y * mWidth + pos.x].mTileType)
        {
            found = true;
            break;
        }
    }
    if(!found) return;

    mTiles[pos.y * mWidth + pos.x].mRegions[regionType] = label;

    depthFirstSearch(whitelist, pos + sf::Vector2i(-1,  0), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(0 ,  1), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(1 ,  0), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(0 , -1), label, regionType);
}
