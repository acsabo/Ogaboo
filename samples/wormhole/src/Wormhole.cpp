#include "Wormhole.h"

using namespace Ogaboo;

Wormhole::Wormhole()
{

    videoScene = new VideoScene(this);
	mainScene = new MainScene(this);
    mainMenuScene = new MainMenuScene(this);

    //loginScene = new LoginScene(this); pau!!
	//immerse = new Immerse(this);
}

bool Wormhole::keyPressed( const OIS::KeyEvent &arg )
{
    if (arg.key == OIS::KC_M)
    {
        this->nextGAHandler();
    }
    if (arg.key == OIS::KC_N)
    {
        this->priorGAHandler();
    }
    GBaseClass::keyPressed(arg);
}

bool Wormhole::keyReleased( const OIS::KeyEvent &arg )
{
	GBaseClass::keyReleased(arg);
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
