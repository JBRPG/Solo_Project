#pragma once

#include "entity.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "terrain.hpp"
#include "explosion.hpp"

#include "sceneGame.hpp"

// Forward declarations
//class Player;

class Enemy : public Entity{

private:

	// From entity
	//int hp;
	//float speed;
	//bool invincible;
	int shootDelay;
	const int delayTime = 60;
	sf::Vector2f spawnVertex;


	// Group related variables
	bool withGroup;
	int groupID; // the enemy is solo if value is set at 0

	// functions

	void destroyEnemy(); // make the enemy explode and disappear

public:



	Enemy(const sf::Texture& tex, int hp, float speed, bool invincible) :
		Entity(tex, hp, speed, invincible), withGroup{ false }, groupID{ 0 },
		spawnVertex{ this->getPosition() }
	{};
	Enemy(const sf::Texture& tex, const sf::IntRect& rect,
		int hp, float speed, bool invincible) :
		Entity(tex, rect, hp, speed, invincible), withGroup{ false }, groupID{ 0 },
		spawnVertex{ this->getPosition() }
	{};

	void setWithGroup(bool group) { this->withGroup = group; };
	bool getWithGroup() { return this->withGroup; };

	void setGroupID(int id) { this->groupID = id; };
	int getGroupID() { return this->groupID; };


	void collideWith(Entity&);
	

	void update(float dt);
	int getTicks() { return ticks; };

	void shootEnemy(float dt); // Will fire after set time period for now..
	void moveEnemy(); // Will use movement class to update enemy movement
	void resetDelay() { shootDelay = delayTime; };

	// I want the enemy to have dynamic movement
	// I will implement it later

	void updateMovement(Movement&);


};