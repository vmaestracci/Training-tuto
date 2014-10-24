#include "TextureManager.h"

void TextureManager::loadTexture(std::string const& name, std::string const& filepath)
{
    sf::Texture t;
    t.loadFromFile(filepath);

    mTextures[name] = t;
}

sf::Texture& TextureManager::getRef(std::string const& name)
{
    return mTextures.at(name);
}
