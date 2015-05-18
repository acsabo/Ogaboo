#ifndef WORMHOLE_H
#define WORMHOLE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>
#include "VideoScene.h"
#include "LoginScene.h"
#include "MainScene.h"
#include "MainMenuScene.h"
#include "Immerse.h"

using namespace Ogaboo;

class Wormhole : public GBaseClass
{
    public:
        Wormhole();
        ~Wormhole();
    protected:

    private:
        VideoScene* videoScene;
        MainMenuScene* mainMenuScene;
        LoginScene* loginScene;
        MainScene* mainScene;
        Immerse* immerse;

};

#endif // WORMHOLE_H
