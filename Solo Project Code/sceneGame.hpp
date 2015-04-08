#pragma once

#include <SFML\Graphics.hpp>

#include "scene.hpp"
#include "game.hpp"
#include "entity.hpp"
#include "movement.hpp"
#include "weapon.hpp"
#include "player.hpp"
#include "collisionGrid.hpp"
#include "spawner.hpp"

// forward declare

class BulletTemplate;

class SceneGame : public Scene{
private:

	sf::View  background1View;
	sf::View  background2View;
	sf::View  gameView;
	sf::View  playerView;
	sf::View  hudView;

	// for temporary purpose, we will have a background sprite
	sf::Sprite background;
	Player* player;
	
	std::vector<Enemy*> enemies; // temporary variable
	std::vector <std::vector < BulletTemplate* > > bullet_Patterns;

	// Other important variables
	collisionGrid gridBox;
	std::vector<Entity*> addList; // We simply add the created entities to EntityList
	std::vector<Entity*> removeList; // we match the stored entities for removal

	std::vector <Spawner*> spawner_list;


public:
	SceneGame(Game* game);
	SceneGame() {}; // dummy constructor to get rid of compiler errors

	// Scene functions
	virtual void draw(float dt);
	virtual void update(float dt);

	void populateGrid();
	void checkCollisions();

	void storeAddedEntity(Entity* entity){
		addList.push_back(entity);
	}
	void storeRemovedEntity(Entity* entity){
		removeList.push_back(entity);
	}

	// From scene
	void addEntity(Entity* entity);

};