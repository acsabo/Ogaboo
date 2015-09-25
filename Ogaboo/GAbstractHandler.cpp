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

GAbstractHandler::GAbstractHandler(std::string name)
{
	cout << "GAbstractHandler::GAbstractHandler" << endl;

	mName = name;
	mOverlaySystem = NULL;
	mWorld = NULL;
	mRayScnQuery = NULL;
	mSceneMgr = NULL;
    this->alive = true;
}

GAbstractHandler::~GAbstractHandler()
{
}

void GAbstractHandler::kill (void)
{
    this->alive = false;
}

bool GAbstractHandler::isAlive (void)
{
    return this->alive;
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
//	Ogre::LogManager::getSingleton().logMessage("*** ---  GAbstractHandler::mouseMoved --- ***", Ogre::LML_NORMAL);
//	this->getCameraSet()->mCameraMan->injectMouseMove(arg);
    return true;
}

bool GAbstractHandler::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
//	Ogre::LogManager::getSingleton().logMessage("*** ---  GAbstractHandler::mousePressed --- ***", Ogre::LML_NORMAL);
//	this->getCameraSet()->mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool GAbstractHandler::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
//	Ogre::LogManager::getSingleton().logMessage("*** ---  GAbstractHandler::mouseReleased --- ***", Ogre::LML_NORMAL);
//	this->getCameraSet()->mCameraMan->injectMouseUp(arg, id);
    return true;
}

CameraSet* GAbstractHandler::getCameraSet (int index)
{
//	Ogre::LogManager::getSingleton().logMessage("*** --- GAbstractHandler::getCameraSet  --- ***", Ogre::LML_NORMAL);
	return mCameraSet[index];
}

void GAbstractHandler::addCameraSet (CameraSet* cameraSet)
{
//	Ogre::LogManager::getSingleton().logMessage("*** --- GAbstractHandler::addCameraSet  --- ***", Ogre::LML_NORMAL);
	this->mCameraSet.push_back(cameraSet);
}

#endif

bool GAbstractHandler::keyPressed( const OIS::KeyEvent &arg )
{
	//Ogre::LogManager::getSingleton().logMessage("*** --- GAbstractHandler::keyPressed  --- ***", Ogre::LML_NORMAL);
//    this->getCameraSet()->mCameraMan->injectKeyDown(arg);
    return true;
}

bool GAbstractHandler::keyReleased( const OIS::KeyEvent &arg )
{
//	this->getCameraSet()->mCameraMan->injectKeyUp(arg);
    return true;
}
