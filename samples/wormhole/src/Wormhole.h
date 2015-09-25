#ifndef WORMHOLE_H
#define WORMHOLE_H

#include <Game.h>
#include "VideoScene.h"

#include "MainScene.h"
#include "MainMenuScene.h"
#include "Immerse.h"
#include "MainMenu.h"

using namespace Ogaboo;

class Wormhole : public Game
{
    public:
        Wormhole();
        ~Wormhole();
    protected:

    private:
        VideoScene* videoScene;
        MainMenuScene* mainMenuScene;
        MainMenu* mainMenu;

        MainScene* mainScene;
        Immerse* immerse;
        bool keyPressed( const OIS::KeyEvent &arg );
        bool keyReleased( const OIS::KeyEvent &arg );
};

#endif // WORMHOLE_H
