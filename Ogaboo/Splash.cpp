/*
 * Splash.cpp
 *
 *  Created on: 14 de set de 2015
 *      Author: acsab
 */

#include "Splash.h"

namespace Ogaboo {

Splash::Splash():GAbstractHandler("splash")
{
	mCameraSet = new Camera_Set();
}

Splash::~Splash() {
	// TODO Auto-generated destructor stub
	delete mSceneMgr;
	delete mCameraSet;
}

} /* namespace Ogaboo */

bool Splash::keyPressed( const OIS::KeyEvent &arg )
{
	Ogre::LogManager::getSingleton().logMessage("*** ---  Splash::keyPressed --- ***", Ogre::LML_NORMAL);

	if (arg.key == OIS::KC_ESCAPE)
	{
		return false;
    }
    return true;
}

void Splash::setup(const Ogaboo::GBaseClass* base)
{
	game = base;
	Ogre::LogManager::getSingleton().logMessage("*** --- Splash::setup  --- ***", Ogre::LML_NORMAL);
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

    mCameraSet->mCamera = camera;
//    mCameraSet->mCameraMan = cameraMan;
    this->addCameraSet(mCameraSet);

    // Alter the camera aspect ratio to match the viewport
//    camera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
	Ogre::LogManager::getSingleton().logMessage("*** --- Splash::setup end  --- ***", Ogre::LML_NORMAL);

//	void Splash::createScene(void)

	Ogre::Entity* entGround2 = mSceneMgr->createEntity("objeto2", "Stair.mesh");
    entGround2->setCastShadows(true);
    Ogre::SceneNode* nodeCursor2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeCursor2->setScale(1, 1, 1);
    nodeCursor2->attachObject(entGround2);
    nodeCursor2->setPosition(4, -4, 0);

	Ogre::LogManager::getSingleton().logMessage("*** --- Splash::createScene END  --- ***", Ogre::LML_NORMAL);
}

void Splash::load(const Ogaboo::GBaseClass* base)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- Splash::load  --- ***", Ogre::LML_NORMAL);
	// load layout
	MyGUI::LayoutManager::getInstance().loadLayout("sample.layout");

	MyGUI::ButtonPtr button = MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("MyFirstButton");
	button->eventMouseButtonClick += MyGUI::newDelegate(this, &Splash::exit);

	button->setNeedMouseFocus(true);
	button->eventMouseSetFocus += MyGUI::newDelegate(this, &Splash::notifyMouseSetFocus);

	OgreOggSound::OgreOggSoundManager* soundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
	// Create a streamed sound, no looping, no prebuffering
	soundManager->createSound("mOver", "test.ogg", true, false, false);
}

void Splash::exit(MyGUI::WidgetPtr _sender)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- Splash::exit  --- ***", Ogre::LML_NORMAL);
}

void Splash::notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- Splash::notifyMouseSetFocus  --- ***", Ogre::LML_NORMAL);
    OgreOggSound::OgreOggSoundManager* soundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    soundManager->getSound("mOver")->play();
}

bool Splash::draw(const Ogre::FrameEvent& evt)
{
//	Ogre::LogManager::getSingleton().logMessage("*** --- Splash::draw  --- ***", Ogre::LML_NORMAL);
    return true;
}
