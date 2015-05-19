/*
 * Game.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: Adriano
 */

#include "Game.h"
#include <iostream>

using namespace std;
using namespace Acsabo;

namespace Acsabo {

Game::Game() {
	//loginScene = new LoginScene(this);
	mainScene = new MainScene(this);
}

Game::~Game() {
	delete mainScene;
	delete loginScene;
}

}

/**
 * START THE GAME
 */

int main()
{
	Game* game = new Game();

	game->go();

    return 0;
}
