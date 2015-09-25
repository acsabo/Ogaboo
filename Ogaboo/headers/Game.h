/*
 * Game.h
 *
 *  Created on: 14 de set de 2015
 *      Author: acsab
 */

#ifndef HEADERS_GAME_H_
#define HEADERS_GAME_H_

#include <GBaseClass.h>
#include <GAbstractHandler.h>
#include <Splash.h>
#include <tr1/unordered_map>

namespace Ogaboo {

class Game : public GBaseClass {
public:

	Game(bool createSplash = false);
	virtual ~Game();

    //create splash screen
	Splash* mSplash;

};

} /* namespace Ogaboo */

#endif /* HEADERS_GAME_H_ */
