#pragma once

#include <SFML\Graphics.hpp>

//#include "sceneGame.hpp"

/*
   Entity inherits all public and protected data and functions from
   Sprite class. Sprite inherits from both Drawable and Transformable.

   Because Entity uses drawing, transformation, and sprite functions,
   it takes only one inheritence from Sprite to reduce coding burdens.
   
*/

// forward declare
class SceneGame;


class Entity : public sf::Sprite{

private:

	int health;
	float speed;
	sf::Time spawntime;
	bool invincible;


protected:

	SceneGame *myScene; // let's keep it at null
	                       // since setScene will take care of it




public:

	/*
	   First let's make the constructors that take only
	   Sprite's parameters
	*/

	Entity(const sf::Texture& tex) :Sprite(tex),
		health{ 1 }, speed{ 0 }, invincible{ true }
	{
		setOrigin(this->getGlobalBounds().width/2, this->getGlobalBounds().height/2);
	};
	Entity(const sf::Texture& tex, const sf::IntRect& rect) :
		Sprite(tex, rect),
		health{ 1 }, speed{ 0 }, invincible{ true }
	{
		setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2);
	};

	/*
	   Then we make constructors that have their own parameters
	   AFTER placing Sprite's parameters first
	*/
	Entity(const sf::Texture& tex, int hp, float speed, bool invincible) :
		Sprite(tex)
	{
		setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2);
	};
	Entity(const sf::Texture& tex, const sf::IntRect& rect,
		int hp, float speed, bool invincible) :
		Sprite(tex, rect)
	{
		setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2);
	};

	// Member functions

	virtual void update(float dt);

	virtual void collideWith(Entity&) = 0;
	// Right now the derived classes of collideWIth are not being called,
	// even with the virtual removed

   
	void setHealth(int hp) { this -> health = hp; };
	int getHealth() { return health; };
	void setSpeed(float speed) { this->speed = speed; };
	float getSpeed() { return speed; };
	void setInvincibility(bool invincible) { this->invincible = invincible; };
	bool getInvincibility() { return invincible; };

	void setScene(SceneGame *scene){myScene = scene;};
    SceneGame* getScene(){return myScene;};



};