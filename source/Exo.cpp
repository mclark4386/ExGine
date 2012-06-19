#include <iostream>
#include "../ExGine/game.h"

void printHelp();

int main(int argc, char** argv)
{
	Game* meGame = Game::getInstance();
	meGame->init(argc,argv);
	meGame->run();
}
