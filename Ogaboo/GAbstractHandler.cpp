#include "GAbstractHandler.h"
#include "GBaseClass.h"

#include <iostream>
using namespace std;

using namespace Acsabo;

static bool isMouseDragging = false;

GAbstractHandler::GAbstractHandler(Acsabo::GBaseClass *base, bool autoCreateScene)
{
    this->alive = true;
    this->setAutoCreateScene(autoCreateScene);

    this->game = base;
    this->game->addHandler(this);
}

GAbstractHandler::~GAbstractHandler()
{
    //dtor
}

void GAbstractHandler::kill (void)
{
    this->alive = false;
}

bool GAbstractHandler::isAlive (void)
{
    return this->alive;
}

void GAbstractHandler::setAutoCreateScene (bool autoCreateScene)
{
    this->autoCreateScene = autoCreateScene;
}

bool GAbstractHandler::getAutoCreateScene ()
{
    return this->autoCreateScene;
}

bool GAbstractHandler::draw(const Ogre::FrameEvent& evt)
{
    return true;
}

bool GAbstractHandler::keyPressed( const OIS::KeyEvent &arg )
{
    mCameraMan->injectKeyDown(arg);
    return true;
}

bool GAbstractHandler::keyReleased( const OIS::KeyEvent &arg )
{
    mCameraMan->injectKeyUp(arg);
    return true;
}

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
bool GAbstractHandler::touchMoved( const OIS::MultiTouchEvent &arg )
{
    if (isMouseDragging)
        mCameraMan->injectMouseMove(arg);
    return true;
}

bool GAbstractHandler::touchPressed( const OIS::MultiTouchEvent &arg)
{
    mCameraMan->injectMouseDown(arg);
//???????????? rever isto!!! no android
   // if (id  == OIS::MB_Right)
    {
        isMouseDragging = true;
    }
    return true;
}

bool GAbstractHandler::touchReleased( const OIS::MultiTouchEvent &arg)
{
    mCameraMan->injectMouseUp(arg);
    isMouseDragging = false;
    return true;
}		

bool GAbstractHandler::touchCancelled( const OIS::MultiTouchEvent &arg )
{
	return false;//???????????
}
#else

bool GAbstractHandler::mouseMoved(const OIS::MouseEvent &arg)
{
    if (isMouseDragging)
    	mCameraMan->injectMouseMove(arg);
    return true;
}

bool GAbstractHandler::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    mCameraMan->injectMouseDown(arg, id);

    if (id  == OIS::MB_Right)
    {
        isMouseDragging = true;
    }
    return true;
}

bool GAbstractHandler::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	mCameraMan->injectMouseUp(arg, id);
    isMouseDragging = false;
    return true;
}

#endif
