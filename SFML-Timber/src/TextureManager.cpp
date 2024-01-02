#include "TextureManager.h"


TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	// Delete all of the textures we used
	sf::Texture* texture;
	std::unordered_map<std::string, sf::Texture*>::iterator iter = mTextures.begin();
	while (iter != mTextures.end())
	{
		texture = iter->second;
		delete texture;
		iter++;
	}
}

std::unordered_map<std::string, sf::Texture*> TextureManager::mTextures;

sf::Texture* TextureManager::GetTexture(std::string name)
{
	if (mTextures.find(name) != mTextures.end())
	{
		return mTextures[name];
	}
	else 
	{
		return nullptr;
	}
}

bool TextureManager::LoadTexture(std::string filename, std::string textureName)
{
	// Haven't loaded it yet, time to create it
	sf::Texture* texture = new sf::Texture();

	if (texture->loadFromFile(filename))
	{
		mTextures[textureName] = texture;
		return true;
	}
	else
	{
		delete texture;
		return false;
	}
}

