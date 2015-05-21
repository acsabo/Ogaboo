/*
 * MainScene.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: Adriano
 */

#include "LControl.h"
#include "MainScene.h"

#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreEntity.h>
#include <iostream>
#include <map>

//#include <GNetworking.h>

using namespace std;


namespace Acsabo {
LControl* lControl = NULL;

map<std::string, GObj*> objects;

MainScene::MainScene(GBaseClass *base) : GAbstractHandler(base, true)
{

}

MainScene::~MainScene() {

}

void MainScene::addObject(const std::string name, GObj* obj) {
	Ogre::Entity* entity = mSceneMgr->createEntity(name, obj->getFileName());
	entity->setCastShadows(true);
	obj->mEntity= entity;

	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->setPosition (0, 0, 0);
	node->attachObject(entity);
	obj->mNode = node;

	//add to list
	objects[name] =  obj;

cout << " added " << name;
}

void callback(const char* data_, int max_length)
{
	std::cout.write(data_, max_length);
	std::cout << std::endl;
}

void MainScene::setup(void)
{
	Ogre::LogManager::getSingleton().logMessage("*** ---  MainScene::setup1 --- ***", Ogre::LML_NORMAL);
    // Get the SceneManager, in this case a generic one
    mSceneMgr = this->game->mRoot->createSceneManager(Ogre::ST_GENERIC);

    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(15,15,15));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    // Create one viewport, entire window
    Ogre::Viewport* vp = this->game->mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));


    //Networking
 //   GNetworking::instance().setCallback(&callback);

	//connect
//	GNetworking::instance().start("appz", "acsabo", "password");
    Ogre::LogManager::getSingleton().logMessage("*** ---  MainScene::setup --- ***", Ogre::LML_NORMAL);

}

bool MainScene::keyPressed( const OIS::KeyEvent &arg )
{

    if (arg.key == OIS::KC_HOME)
    {
    }

    if (arg.key == OIS::KC_ESCAPE)
    {
    	//quit
    	//GNetworking::instance().quit();
    }

    GAbstractHandler::keyPressed(arg);

    return true;
}

void MainScene::createScene(void)
{
    Ogre::LogManager::getSingleton().logMessage("*** ---  MainScene::setup2 --- ***", Ogre::LML_NORMAL);

	lControl = new LControl(this, "test_adr.lua");
	lControl->run();
    Ogre::LogManager::getSingleton().logMessage("*** ---  MainScene::setup3 --- ***", Ogre::LML_NORMAL);

//	boost::thread mythread(&LControl::run, lControl);
//
//	cout << " criado! " << endl;
//	mythread.start_thread();

//	GObj* o = new GObj("models/Earth.mesh");
//	addObject("earth", o);

//
//    // Set idle animation
//	o->mAnimationState = o->mEntity->getAnimationState("Idle");
//    o->mAnimationState->setLoop(true);
//    o->mAnimationState->setEnabled(true);
//	// Create the walking list
//	o->mWalkSpeed = 35.0f;
//	o->mWalkList.push_back(Ogre::Vector3(550.0f,  0.0f,  50.0f ));
//	o->mWalkList.push_back(Ogre::Vector3(-100.0f,  0.0f, -200.0f));
//
//	o = new GObj("models/robot.mesh");
//	addObject("teste2", o);
//    // Set idle animation
//	o->mAnimationState = o->mEntity->getAnimationState("Idle");
//    o->mAnimationState->setLoop(true);
//    o->mAnimationState->setEnabled(true);
//	// Create the walking list
//	o->mWalkSpeed = 35.0f;
//	o->mWalkList.push_back(Ogre::Vector3(450.0f,  0.0f,  150.0f ));
//	o->mWalkList.push_back(Ogre::Vector3(-130.0f,  0.0f, -230.0f));

}

char request[] = "appz:acsabo:update: blah blah blah :\0";

bool MainScene::draw(const Ogre::FrameEvent& evt)
{
    Ogre::LogManager::getSingleton().logMessage("*** ---  MainScene::setup5 --- ***", Ogre::LML_NORMAL);

	for ( auto local_it = objects.begin(); local_it!= objects.end(); ++local_it  )
	{
		GObj* obj = local_it->second;
		obj->Update(evt.timeSinceLastFrame);


//		GNetworking::instance().send(request);

	}
	mCameraMan->frameRenderingQueued(evt);
    return true;
}

}
