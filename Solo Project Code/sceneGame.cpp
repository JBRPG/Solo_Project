#include "sceneGame.hpp"
#include "input.hpp"


SceneGame::SceneGame(Game* game){

	this->game = game; // need this to run the game.

	// Set up the view layers

	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->background1View.setSize(pos);
	this->background2View.setSize(pos);
	this->gameView.setSize(pos);
	this->playerView.setSize(pos);
	this->hudView.setSize(pos);
	pos *= 0.5f;
	this->background1View.setCenter(pos);
	this->background2View.setCenter(pos);
	this->gameView.setCenter(pos);
	this->playerView.setCenter(pos);
	this->hudView.setCenter(pos);

	// Initialize the background

	background = sf::Sprite(this->game->texmgr.getRef("background"));

	// setup the bullet patterns

	// Hardcoded for testing purposes
	
	std::vector<BulletTemplate*> player_weapon;

	// Typical 3-way gun
	player_weapon.push_back(new BulletTemplate("bulletPlayer", 1, 15, false, 0));
	player_weapon.push_back(new BulletTemplate("bulletPlayer", 1, 15, false, -15));
	player_weapon.push_back(new BulletTemplate("bulletPlayer", 1, 15, false, 15));

	// simple rapid fire


	bullet_Patterns.push_back(player_weapon);

	std::vector<BulletTemplate*> enemy_weapon;

	// 2 shot rapid
	enemy_weapon.push_back(new BulletTemplate("bulletEnemy", 1, 10, false, -5));
	enemy_weapon.push_back(new BulletTemplate("bulletEnemy", 1, 10, false, 5));

	bullet_Patterns.push_back(enemy_weapon);


	// initalize Movement

	std::vector<sf::Vector2f> waypoints = {
		sf::Vector2f(-100, 0),
		sf::Vector2f(-100, -100),
		sf::Vector2f(0, -100),
	};

	Movement* enemy_movement = new Movement(sf::Vector2f (400, 400),waypoints);

	std::vector <int> spawnParams = { 60 };
	// Initalize the spawner
	spawner_list.push_back(new Spawner(
		new Weapon(enemy_weapon, "sequence_enemy", 60, { 8 }),
		enemy_movement,
		EnemyTemplate(this,"enemySprite",1, 2, false,
		sf::Vector2f(400, 400)), spawnParams));


	// Initialize the entities

	// for now we just add in the player and a few enemies
	// hardcoded until we make use of the random generator

	player = new Player(this->game->texmgr.getRef("playerSprite"),
		1, 5, false, 3);
	player->setPosition(sf::Vector2f(100, 300));
	player->setWeapon(new Weapon((bullet_Patterns[0]), "single", 60));

	addEntity(player);


	/*

    // For a simple test, we will add in a few enemies
	enemies.push_back(nullptr);
	enemies[0] = new Enemy(this->game->texmgr.getRef("enemySprite"),
		1,1,false);
    enemies[0]->setPosition(sf::Vector2f(400, 400));
	enemies[0]->setWeapon(new Weapon(bullet_Patterns[1], "sequence_enemy", 60, {8}));

	enemies[0]->setMovement(enemy_movement);



	addEntity(enemies[0]);

	enemies.push_back(nullptr);
	enemies[1] = new Enemy(this->game->texmgr.getRef("enemySprite"),
		1, 1, false);
	enemies[1]->setPosition(sf::Vector2f(400, 300));
	enemies[1]->setWeapon(new Weapon(bullet_Patterns[1], "sequence_enemy", 60, { 8 }));

	enemies[1]->setMovement(enemy_movement);

	addEntity(enemies[1]);

	//*/

}

void SceneGame::draw(float dt){

	// draw the background
	this->game->window.setView(background1View);
	this->game->window.draw(background);

	// draw the entities

	this->game->window.setView(gameView);

	for (int i = 0; i < getEntitysize(); ++i){
		sf::Sprite* idxSprite = getEntity(i);
		this->game->window.draw(*idxSprite);
	}

}

void SceneGame::update(float dt){

	for (auto spawn : spawner_list){
		spawn->update();
	}

	///update the entities inside the current EntityList
	for (int i = 0; i < getEntitysize(); ++i){
		Entity* idxEntity = getEntity(i);
		idxEntity->update(dt);
	}

	// Add the created entities

	for (auto entity : addList){
		addEntity(entity);
	}

	// Now check collisions

	checkCollisions();

	
	// if there are no entities to erase, update is complete
	if (!removeList.empty()){

		// remove the destroyed entities
		// must iterate backwards for both vector-based entity lists

		for (int j = removeList.size() - 1; j >= 0; --j){
			// check the entities one by one
			for (int k = EntityList.size() - 1; k >= 0; --k){

				// remove from entity list if searched entity is found

				// Since iterators act as pointers, they can be dereferenced to
				// access the current element being searched
				// to make sure they point to the same Entity

				Entity* p = removeList[j]; // pointer to entities in removeList
				Entity* q = EntityList[k]; // pointer to entities in EntityList

				if (p == q){
					// remove entity from entityList
					delete p;
					EntityList.erase(EntityList.begin() + k);
					

					break;
				}

			}

		}
	}


	//empty the containers of added and removed entities 
	addList.clear();
	removeList.clear();


}

/*
  These collision-based functions are responsible
  for managing all the entities on screen.
  
  populateGrid will place the entities at the appropriate cells.

  checkCollisions will compare entities within occupied cells.
  If the two unique entities actually collide, then do the collision
  work between the two.


*/

void SceneGame::populateGrid(){

	gridBox.reset();

	// Set up the rectangle to represent the cell.
	// Default is at top left corner
	sf::FloatRect cellRect = sf::FloatRect
		(sf::Vector2f(0,0),sf::Vector2f(
				game->window.getSize().x/gridBox.slicesX,
				game->window.getSize().y/gridBox.slicesY));
	sf::FloatRect windowRect = sf::FloatRect(0, 0,
		game->window.getSize().x, game->window.getSize().y);
    // Now we check each entity if they are inside the grid

	for (int i = 0; i < getEntitysize(); ++i){

		// if entity is outside the game window,
		// store the entity and continue with the rest of the entities

		if (!getEntity(i)->getGlobalBounds().intersects(windowRect)){
			storeRemovedEntity(getEntity(i));
			continue;
	    }



		for (auto x = 0; x < gridBox.slicesX; ++x){
			for (auto y = 0; y < gridBox.slicesY; ++y){

				// Set up the 4 corners for the cell's area

				// had to do float casting for more precise cells
				cellRect.left = float(game->window.getSize().x) *
					            (float(x) / float(gridBox.slicesX));
				cellRect.top = float(game->window.getSize().y) *
					            (float(y) / float(gridBox.slicesY));
				cellRect.width = float(game->window.getSize().x) *
					            (float(x+1) / float(gridBox.slicesX));
				cellRect.height = float(game->window.getSize().y) *
					            (float(y+1) / float(gridBox.slicesY));


				// Add the entitiy to the cell if they touch

				if (getEntity(i)->getGlobalBounds().intersects(cellRect)){
					gridBox.append(x, y, getEntity(i));
				}


			}
		}


	}
}

void SceneGame::checkCollisions(){

	populateGrid();


	for (auto i = 0; i < gridBox.slicesX; ++i){
		for (auto j = 0; j < gridBox.slicesY; ++j){
			if (gridBox.cell[i][j].nEntities < 2) continue;

			for (auto k = 0; k < gridBox.cell[i][j].nEntities; ++k){
				for (auto l = 0; l < gridBox.cell[i][j].nEntities; ++l){

					// Set up the pointers and compare them
					auto p = gridBox.cell[i][j].items[k];
					auto q = gridBox.cell[i][j].items[l];
					if (p == q) continue; // we do not want the same pointer

					if (p->getGlobalBounds().
						intersects(q->getGlobalBounds() )){

						// Do a series of collisions depending on the specific entities
						p->collideWith(*q);

					}


				}
			}
		}
	}

}

/*
   Functions derived from Scene
*/

void SceneGame::addEntity(Entity* entity){
	entity->setScene(this);
	EntityList.push_back(entity);
}

