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

	__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** MainScene::addObject ***");
}


OgreBites::SdkCameraMan* mCameraMan2;
void MainScene::setup(void)
{
    // Get the SceneManager, in this case a generic one
	mSceneMgr = this->game->mRoot->createSceneManager(Ogre::ST_GENERIC);
    //mSceneMgr = this->game->mRoot->createSceneManager("DefaultSceneManager");

    // Create the camera
    mCamera = mSceneMgr->createCamera("MyCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(2,18,18));

    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(1);

    // Create the camera 2
	Ogre::Camera* mCamera2 = mSceneMgr->createCamera("PlayerCam2");
	// Position it at 500 in Z direction
	mCamera2->setPosition(Ogre::Vector3(2,18,18));

	// Look back along -Z
	mCamera2->lookAt(Ogre::Vector3(0,0,0));
	mCamera2->setNearClipDistance(1);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);

	mCameraMan2 = new OgreBites::SdkCameraMan(mCamera2);

    // Create one viewport, entire window
    Ogre::Viewport* vp = this->game->mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue::Black);
    vp->setDimensions(0,0,0.5,1);

    Ogre::Viewport* vp2 = this->game->mWindow->addViewport(mCamera2, 1);
    vp2->setBackgroundColour(Ogre::ColourValue::Black);
    vp2->setDimensions(0.5,0,0.5,1);

    //Shader
	bool success = initialiseRTShaderSystem(mSceneMgr);
	if (!success)
	{
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND,
			"Shader Generator Initialization failed - Core shader libs path not found",
			"SampleBrowser::createDummyScene");
	}

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(2*vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mCamera2->setAspectRatio(Ogre::Real(2*vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

    __android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** MainScene::setup end***");

    Ogre::Root::getSingleton().getRenderSystem()->setFixedPipelineEnabled(false);
}

bool MainScene::keyPressed( const OIS::KeyEvent &arg )
{
    GAbstractHandler::keyPressed(arg);

    if (arg.key == OIS::KC_HOME)
    {
    }
    return true;
}

void MainScene::createScene(void)
{
    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");

    light->setType(Ogre::Light::LT_POINT);

    light->setType(Ogre::Light::LT_POINT);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);
    light->setPosition(0,0,0);

	__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** MainScene::createScene ***");
//	lControl = new LControl(this, "test_adr.lua");
//	lControl->run();

//	//boost::thread mythread(&LControl::run, lControl);
//
//	cout << " criado! " << endl;
//	//mythread.start_thread();

	GObj* o1 = new GObj("models/Ramp.mesh");
	addObject("teste1", o1);

	/**
	GObj* o = new GObj("models/robot.mesh");
	addObject("teste1", o);

    // Set idle animation
	o->mAnimationState = o->mEntity->getAnimationState("Idle");
    o->mAnimationState->setLoop(true);
    o->mAnimationState->setEnabled(true);
	// Create the walking list
	o->mWalkSpeed = 35.0f;
	o->mWalkList.push_back(Ogre::Vector3(0.0f,  0.0f,  50.0f ));
	o->mWalkList.push_back(Ogre::Vector3(-100.0f,  0.0f, -200.0f));
	*/
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

bool MainScene::draw(const Ogre::FrameEvent& evt)
{
	__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** MainScene::draw ***");
	for ( auto local_it = objects.begin(); local_it!= objects.end(); ++local_it  )
	{
		GObj* obj = local_it->second;
		obj->Update(evt.timeSinceLastFrame);
	}
	mCameraMan->frameRenderingQueued(evt);
	mCameraMan->frameRenderingQueued(evt);

    return true;
}

}
