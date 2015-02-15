#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager{

private:
	// Texture array used
	std::map<std::string, sf::Texture> textures;

public:

	// Add texture from file
	void loadTexture(const std::string& name, const std::string& filename);

	// Translate the id into reference
	sf::Texture& getRef(const std::string& texture);

	// Constructor
	TextureManager(){};

};