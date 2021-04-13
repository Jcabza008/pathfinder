#pragma once

#include <map>
#include <memory>

namespace pathfinder { namespace view {

	class TextureProvider
	{
	public:
		TextureProvider();
		TextureProvider(const std::vector<std::string>& paths);

		TextureProvider& loadTextures(const std::vector<std::string>& paths);
		const sf::Texture& getTexture(const std::string& id) const;

	private:
		std::string stripPath(const std::string& path);

		std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	};

}}