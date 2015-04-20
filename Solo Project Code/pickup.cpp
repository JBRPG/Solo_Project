#include "pickup.hpp"

#include "player.hpp"

void Pickup::collideWith(Entity& other){
	if (Player* player = dynamic_cast<Player*> (&other)){
		myScene->storeRemovedEntity(this);
	}
}