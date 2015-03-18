#pragma once

#include <SFML\Graphics.hpp>

#include "entity.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "terrain.hpp"

#include "sceneGame.hpp"

// forward declaration ??
//class Player;
//class Enemy;

class Bullet : public Entity{

private:
	// From entity
	//int hp;
	//float speed;
	//bool invincibility;

	bool enemyShot; // if false, then player shot bullet
	float rotation;


public:

	// constructors

	Bullet(const sf::Texture& tex, int hp, float speed, bool invincibility,
		bool enemyShot, float rot) :
		rotation{rot},
		Entity(tex, hp, speed, invincibility)
	{
		this->setRotation(rot);
	};

	Bullet(const sf::Texture& tex, const sf::IntRect& rect, int hp, float speed, bool invincibility,
		bool enemyShot, float rot) :
		rotation{ rot },
		Entity(tex, rect, hp, speed, invincibility)
	{
		this->setRotation(rot);
	};

	// member functions

	void setEnemyShot(bool shot) { enemyShot = shot; };
	bool getEnemyShot() { return enemyShot; };


	void collideWith(Entity&);
	void update (float dt);
	int getTicks() { return ticks; };

	// I want the bullet to have dynamic movement
	// and will be implemented later

	// For now, we leave the updateMovement empty
	void updateMovement(Movement&) {};

	
};