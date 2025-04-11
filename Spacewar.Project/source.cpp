#include "Game.h"

int main() {
	//Init Game
	Game game;
	//GAMELOOP
	while (game.getWindowIsOpen())
	{
		//Update
		game.update();
		//Render
		game.render();
	}
	return 0;
}