#include "textureManager.hpp"

void TextureManager::loadTexture(const std::string& name, const std::string& filename){

	// Load texture
	sf::Texture tex;
	tex.loadFromFile(filename);

	// add to list of textures
	this->textures[name] = tex;
}

sf::Texture& TextureManager::getRef(const std::string& texture){
	return this->textures.at(texture);
}