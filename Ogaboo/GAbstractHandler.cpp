/*
 * Ogaboo (Open Game Bootstrap) 1.0
 * https://sourceforge.net/projects/ogaboo/
 *
 * Copyright (c) 2014 Adriano de Castro Sabo
 * acsabo@hotmail.com
 *
 * Licensed under http://opensource.org/licenses/MIT
 */

#include "GAbstractHandler.h"
#include "GBaseClass.h"

#include <iostream>
using namespace std;

using namespace Ogaboo;

//static bool isMouseDragging = false;

GAbstractHandler::GAbstractHandler(Ogaboo::GBaseClass *base, bool autoCreateScene)
{
	mOverlaySystem = NULL;
	mWorld = NULL;
	mRayScnQuery = NULL;
	mSceneMgr = NULL;
	this->autoCreateScene = autoCreateScene;
    this->alive = true;
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
    this->getCameraSet()->mCameraMan->injectKeyDown(arg);
    return true;
}

bool GAbstractHandler::keyReleased( const OIS::KeyEvent &arg )
{
	this->getCameraSet()->mCameraMan->injectKeyUp(arg);
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

//bool GAbstractHandler::mouseMoved(const OIS::MouseEvent &arg)
//{
//    if (isMouseDragging)
//    	mCameraMan->injectMouseMove(arg);
//    return true;
//}
//
//bool GAbstractHandler::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
//{
//    mCameraMan->injectMouseDown(arg, id);
//
//    if (id  == OIS::MB_Right)
//    {
//        isMouseDragging = true;
//    }
//    return true;
//}
//
//bool GAbstractHandler::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
//{
//	mCameraMan->injectMouseUp(arg, id);
//    isMouseDragging = false;
//    return true;
//}

CameraSet* GAbstractHandler::getCameraSet (int index)
{
	return mCameraSet[index];
}

void GAbstractHandler::addCameraSet (CameraSet* cameraSet)
{
	this->mCameraSet.push_back(cameraSet);
}

#endif
