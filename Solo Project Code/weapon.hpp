#pragma once

#include <SFML/Graphics.hpp>

#include "bullet.hpp"
#include "sceneGame.hpp"

#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"


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

	int rapidRate; // How many shots per second
	int rapidRateSet;
	int rapidDuration;
	int rapidDurationSet;

	// Enemy only
	int sequenceDelayTime; // delay time between individual bullets 
	int sequenceDelaySet;

	// Player only
	int holdDurationTime; // player does not let go, shot enter cooldown
	int holdDurationSet;  // otherwise, weapon ready to fire when pressed

	int spawnTime;

	std::string keyword; // Determines behavior of weapon

	std::vector<BulletTemplate> bullet_list;
	bool enemydidShoot;


public:

	// Constructors

	Weapon(std::vector <BulletTemplate>, std::string, int, std::vector<int>);




	// Functions

	void update();

	/*
	   Look up the name of the specified shot type to
	   call the specified functions
	*/
	void lookupShoot(Entity&, std::string);


	void shootBullets(Entity&); // Shoot all bullets at once


	void shootBulletSequence(Entity&); // shoot one bullet each in a sequence
};