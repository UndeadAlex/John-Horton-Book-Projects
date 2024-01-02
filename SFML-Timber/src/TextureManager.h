#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	static bool LoadTexture(std::string filename, std::string textureName);
	static sf::Texture* GetTexture(std::string textureName);

private:
	static std::unordered_map<std::string, sf::Texture*> mTextures;
};

#endif // TEXTURE_MANAGER_H