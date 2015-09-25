/*
 * Game.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: acsab
 */

#include <Game.h>

namespace Ogaboo {

Game::Game(bool createSplash) {
	if (createSplash)
	{
		mSplash = new Splash();
		this->addHandler("splash", mSplash);
		this->setCurrentHandler("splash");
	}
}

Game::~Game() {
	delete mSplash;
}

} /* namespace Ogaboo */
