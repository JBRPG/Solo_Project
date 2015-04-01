#pragma once

#include <SFML/Graphics.hpp>

#include "bullet.hpp"

/*
  Weapon consist of a collection of bullets

  There will be two types of Weapon objects
   - Player variant will be pressed by the shoot button
   - Enemy variant will shoot bullets after a set period of time

  Bullets can be all shot at the same time, or in a specified sequence based on time (in ticks)


*/

class Weapon{
private:

	// Delay types
	int shootCooldownTime; // general delay time until shooting
	int shootCooldownSet;  

	int rapidDurationTime; // duration of rapid fire
	int rapidDurationSet;

	// Enemy only
	int sequenceDelayTime; // delay time between individual bullets 
	int sequenceDelaySet;

	// Player only
	int holdDurationTime; // player does not let go, shot enter cooldown
	int holdDurationSet;  // otherwise, weapon ready to fire when pressed

	int spawnTime;

	std::string keyword; // Determines behavior of weapon

	std::vector<Bullet> bullet_list;


public:

	// Constructors

	Weapon(std::vector <Bullet>, std::string, int, int);




	// Functions

	void update();

	void lookupShoot(Entity&, std::string);

	/*
	    Table functions based on the following parameters
		1 - Entity&:  need entity to generate the bullets
		2 - sf::Vector2f:
		3 - 
	*/
};