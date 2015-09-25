/*
 * MainMenu.cpp
 *
 *  Created on: 11 de set de 2015
 *      Author: acsab
 */

#include "MainMenu.h"

MainMenu::MainMenu() : GAbstractHandler("mainMenu")
{
	cout << "MainMenu::MainMenu()" << endl;
	mCameraSet = new Camera_Set();
}

MainMenu::~MainMenu() {
	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::~MainMenu  --- ***", Ogre::LML_NORMAL);
	delete mCameraSet;
}

void MainMenu::setup(const Ogaboo::GBaseClass* base)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::setup  --- ***", Ogre::LML_NORMAL);
    // Get the SceneManager, in this case a generic one
    mSceneMgr = base->mRoot->createSceneManager(Ogre::ST_GENERIC);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

    // Create the camera
    Ogre::Camera* camera = mSceneMgr->createCamera("PlayerCam");
    // Position it at 500 in Z direction
    camera->setPosition(Ogre::Vector3(15,15,15));
    // Look back along -Z
    camera->lookAt(Ogre::Vector3(0,0,0));
    camera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(camera);
    mCameraSet->mCamera = camera;
    this->addCameraSet(mCameraSet);

	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::setup end  --- ***", Ogre::LML_NORMAL);

	Ogre::Entity* entGround2 = mSceneMgr->createEntity("objeto", "Stair.mesh");
    entGround2->setCastShadows(true);
    Ogre::SceneNode* nodeCursor2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeCursor2->setScale(1, 1, 1);
    nodeCursor2->attachObject(entGround2);
    nodeCursor2->setPosition(-4, 4, 4);

	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::createScene END  --- ***", Ogre::LML_NORMAL);
}

void MainMenu::load(const Ogaboo::GBaseClass* base)
{

}

void MainMenu::exit(MyGUI::WidgetPtr _sender)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::exit  --- ***", Ogre::LML_NORMAL);
}

void MainMenu::notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::notifyMouseSetFocus  --- ***", Ogre::LML_NORMAL);

    OgreOggSound::OgreOggSoundManager* mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    mSoundManager->getSound("mOver")->play();

}

bool MainMenu::draw(const Ogre::FrameEvent& evt)
{
	mCameraMan->frameRenderingQueued(evt);
    return true;
}

bool MainMenu::keyPressed( const OIS::KeyEvent &arg )
{
	//exit
	if (arg.key == OIS::KC_ESCAPE)
	{
		return false;
	}

	mCameraMan->injectKeyDown(arg);
    return true;
}

bool MainMenu::keyReleased( const OIS::KeyEvent &arg )
{
	mCameraMan->injectKeyUp(arg);
    return true;
}

