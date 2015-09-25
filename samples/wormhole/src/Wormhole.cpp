#include "Wormhole.h"

using namespace Ogaboo;

Wormhole::Wormhole()
{
	cout << "Wormhole::Wormhole()" << endl;
//	mainMenu = new MainMenu();
//	this->addHandler("mainMenu", mainMenu);

    videoScene = new VideoScene();
    this->addHandler("videoScene", videoScene);

//	mainScene = new MainScene(this);

//    mainMenuScene = new MainMenuScene(this);

//	immerse = new Immerse(this);
}

bool Wormhole::keyPressed( const OIS::KeyEvent &arg )
{
//    if (arg.key == OIS::KC_M)
//    {
//        this->nextGAHandler();
//    }
//    if (arg.key == OIS::KC_N)
//    {
//        this->priorGAHandler();
//    }
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
    delete mainMenuScene;
    delete mainScene;
    delete mainMenu;
    delete immerse;
}
