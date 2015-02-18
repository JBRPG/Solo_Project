#pragma once

#include <SFML\Graphics.hpp>

#include "entity.hpp"
#include "enemy.hpp"
#include "player.hpp"

class Bullet : public Entity{

private:
	// From entity
	int hp;
	float speed;
	bool invincibility;

	bool enemyShot; // if false, then player shot bullet


public:

	// constructors

	Bullet(const sf::Texture& tex, int hp, float speed, bool invincibility,
		bool enemyShot) :
		hp{hp},
		speed{speed},
		invincibility{invincibility},
		Entity(tex, hp, speed, invincibility)
	{};

	Bullet(const sf::Texture& tex, const sf::IntRect& rect, int hp, float speed, bool invincibility,
		bool enemyShot) :
		hp{ hp },
		speed{ speed },
		invincibility{ invincibility },
		Entity(tex, rect, hp, speed, invincibility)
	{};

	// member functions

	void setEnemyShot(bool shot) { enemyShot = shot; };
	bool getEnemyShot() { return enemyShot; };


	void collideWith(Player*);
	void collideWith(Enemy*);

};