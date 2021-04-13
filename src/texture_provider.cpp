#include <vector>
#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>

#include "log.h"
#include "texture_provider.h"

namespace pathfinder { namespace view {

    TextureProvider::TextureProvider()
    {
    }

    TextureProvider::TextureProvider(const std::vector<std::string>& paths)
    {
        loadTextures(paths);
    }

    TextureProvider& TextureProvider::loadTextures(const std::vector<std::string>& paths)
    {
        for(const auto& path : paths)
        {
            auto texture = std::make_shared<sf::Texture>();
            texture->loadFromFile(path);
            auto textureKey = stripPath(path);
            m_textures.emplace(textureKey, texture);
        }
        return *this;
    }

    const sf::Texture& TextureProvider::getTexture(const std::string& id) const
    {
        return *(m_textures.at(id));
    }

    std::string TextureProvider::stripPath(const std::string& path)
    {
        auto begin = path.find_last_of("\\/") + 1;
        auto end = path.find_first_of(".", begin);
        return path.substr(begin, end - begin);
    }
}}
