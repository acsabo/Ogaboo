#include "Wormhole.h"

using namespace Ogaboo;

Wormhole::Wormhole()
{
	 //    mainScene = new MainScene(this);

    //ctor
    videoScene = new VideoScene(this);
    //loginScene = new LoginScene(this);
    //mainMenuScene = new MainMenuScene(this);

	//immerse = new Immerse(this);

}

Wormhole::~Wormhole()
{
    //dtor
    delete videoScene;
    delete loginScene;
    delete mainMenuScene;
    delete mainScene;
    delete immerse;
}
