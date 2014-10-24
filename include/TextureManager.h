#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

#include <string>
#include <map>

class TextureManager
{
    public:
        TextureManager() { }

    public:
        void loadTexture(std::string const& name, std::string const& filepath);
        sf::Texture& getRef(std::string const& name);

    private:
        std::map<std::string, sf::Texture> mTextures;
};

#endif // TEXTUREMANAGER_H
