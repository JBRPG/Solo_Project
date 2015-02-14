#pragma once

#include "entity.hpp"

class Enemy : public Entity{

private:

	// Group related variables
	bool withGroup;
	int groupID; // the enemy is solo if value is set at 0

public:



	Enemy(const sf::Texture& tex, int hp, float speed, bool invincible) :
		Entity(tex, hp, speed, invincible), withGroup{ false }, groupID{0}
	{};
	Enemy(const sf::Texture& tex, const sf::IntRect& rect,
		int hp, float speed, bool invincible) :
		Entity(tex, rect, hp, speed, invincible), withGroup{ false }, groupID{ 0 }
	{};

	void setWithGroup(bool group) {this->withGroup = group};
	bool getWithGroup() { return this->withGroup; };

	void setGroupID(int id) { this->groupID = id; };
	int getGroupID() { return this->groupID; };

};