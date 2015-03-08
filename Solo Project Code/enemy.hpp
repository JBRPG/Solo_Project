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
	int hp;
	float speed;
	bool invincible;
	int shootDelay;
	const int delayTime = 60;


	// Group related variables
	bool withGroup;
	int groupID; // the enemy is solo if value is set at 0

	// functions

	void destroyEnemy(); // make the enemy explode and disappear

public:



	Enemy(const sf::Texture& tex, int hp, float speed, bool invincible) :
		hp{ hp }, speed{ speed }, invincible{ invincible },
		Entity(tex, hp, speed, invincible), withGroup{ false }, groupID{0}
	{};
	Enemy(const sf::Texture& tex, const sf::IntRect& rect,
		int hp, float speed, bool invincible) :
		hp{ hp }, speed{ speed }, invincible{ invincible },
		Entity(tex, rect, hp, speed, invincible), withGroup{ false }, groupID{ 0 }
	{};

	void setWithGroup(bool group) { this->withGroup = group; };
	bool getWithGroup() { return this->withGroup; };

	void setGroupID(int id) { this->groupID = id; };
	int getGroupID() { return this->groupID; };


	void collideWith(Entity&);
	

	void update(float dt);
	void shootEnemy(float dt); // Will fire after set time period for now..
	void resetDelay() { shootDelay = delayTime; };

	// I want the enemy to have dynamic movement
	// I will implement it later


};