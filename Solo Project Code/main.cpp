#include <iostream>

#include "game.hpp"
#include "sceneGame.hpp"

using namespace std;

int main(){

	// Let's start out game
	Game game;
	game.pushScene(new SceneGame(&game));
	game.gameLoop();

	return 0;
}