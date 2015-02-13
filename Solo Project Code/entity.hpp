#pragma once

#include <SFML\Graphics.hpp>

/*
   Entity inherits all public and protected data and functions from
   Sprite class. Sprite inherits from both Drawable and Transformable.

   Because Entity uses drawing, transformation, and sprite functions,
   it takes only one inheritence from Sprite to reduce coding burdens.
   
*/


class Entity : public sf::Sprite{

private:

	int health;
	float speed;
	sf::Time spawntime;
	bool invincible;



public:

	/*
	   First let's make the constructors that take only
	   Sprite's parameters
	*/

	Entity(const sf::Texture& tex) :Sprite(tex),
		health{ 0 }, speed{ 0 }, invincible{ true }
	{};
	Entity(const sf::Texture& tex, const sf::IntRect& rect) :
		Sprite(tex, rect),
		health{ 0 }, speed{ 0 }, invincible{ true }
	{};

	/*
	   Then we make constructors that have their own parameters
	   AFTER placing Sprite's parameters first
	*/
	Entity(const sf::Texture& tex, int hp, float speed, bool invincible) :
		Sprite(tex)
	{};
	Entity(const sf::Texture& tex, const sf::IntRect& rect,
		int hp, float speed, bool invincible) :
		Sprite(tex, rect)
	{};

	// Member functions

	void update(sf::Time dt);
	void draw(sf::Time dt);

	void setHealth(int hp) { this -> health = hp; };
	int getHealth() { return health; };
	void setSpeed(float speed) { this->speed = speed; };
	float getSpeed() { return speed; };
	void setInvincibility(bool invincible) { this->invincible = invincible; };
	bool getInvincibility() { return invincible; };



};