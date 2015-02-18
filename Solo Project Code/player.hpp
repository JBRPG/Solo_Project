#pragma once

#include <SFML\Graphics.hpp>

#include "entity.hpp"
#include "bullet.hpp"
#include "enemy.hpp"

#include "input.hpp"

class Player : public Entity{

private:

	unsigned int score = 0;
	float spawnTime = 5.0f;
	unsigned int lives;
	// Powerups ?
	// Weapons ?
	
	// From entity
	int hp;
	float speed;
	bool invincibility;



public:

	Player(const sf::Texture& tex, int hp, float speed, bool invincibility,
		int lives) :
		hp{ hp },
		speed{ speed },
		invincibility{ invincibility },

		Entity(tex, hp, speed, invincibility)
	{};


	Player(const sf::Texture& tex, const sf::IntRect& rect, int hp,
		  float speed, bool invincibility,
		int lives) :
		hp{ hp },
		speed{ speed },
		invincibility{ invincibility },

		Entity(tex, rect, hp, speed, invincibility)
	{};

	void update(float dt);


	void collideWith(Bullet*);
	void collideWith(Enemy*);

	void movePlayer();
	void shootPlayer();

};