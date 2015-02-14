#pragma once

#include <SFML\Graphics.hpp>

#include "entity.hpp"

class Player : public Entity{

private:

	unsigned int score = 0;
	float spawnTime = 5.0f;
	unsigned int lives;
	// Powerups ?
	// Weapons ?


public:

	Player(const sf::Texture& tex, int hp, float speed, bool invincibility,
		int lives) : Entity(tex, hp, speed, invincibility)
	{};


	Player(const sf::Texture& tex, const sf::IntRect& rect, int hp,
		  float speed, bool invincibility,
		int lives) : Entity(tex, rect, hp, speed, invincibility)
	{};

	void move();
	void shoot();

};