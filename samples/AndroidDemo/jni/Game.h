/*
 * Game.h
 *
 *  Created on: Jul 9, 2014
 *      Author: Adriano
 */

#ifndef GAME_H_
#define GAME_H_

#include "GBaseClass.h"
#include "MainScene.h"
#include <cpu-features.h>
namespace Acsabo {

class Game : public GBaseClass {
private:
	MainScene* mainScene;
public:
	Game();
	virtual ~Game();
};

}

#endif /* GAME_H_ */
