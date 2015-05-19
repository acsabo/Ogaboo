#include "Immerse.h"
#include <iostream>

Immerse::Immerse(GBaseClass *base) : GAbstractHandler(base, true)
{
    //ctor
}

Immerse::~Immerse()
{
    //dtor
}

OgreBites::SdkCameraMan* mCameraMan2;

Ogre::Entity* entGround;
Ogre::SceneNode* nodeCursor;

void Immerse::setup(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = this->game->mRoot->createSceneManager(Ogre::ST_GENERIC);

    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(15,15,15));

    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(1);

    // Create the camera 2
    Ogre::Camera* mCamera2 = mSceneMgr->createCamera("PlayerCam2");
    // Position it at 500 in Z direction
    mCamera2->setPosition(Ogre::Vector3(15,15,15));

    // Look back along -Z
    mCamera2->lookAt(Ogre::Vector3(0,0,0));
    mCamera2->setNearClipDistance(1);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    mCameraMan2 = new OgreBites::SdkCameraMan(mCamera2);

    // Create one viewport, entire window
    Ogre::Viewport* vp = this->game->mWindow->addViewport(mCamera);
   // vp->setBackgroundColour(Ogre::ColourValue::Black);
    vp->setDimensions(0,0,0.5,1);

    Ogre::Viewport* vp2 = this->game->mWindow->addViewport(mCamera2, 1);
   // vp2->setBackgroundColour(Ogre::ColourValue::Black);
    vp2->setDimensions(0.5,0,0.5,1);

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(2*vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mCamera2->setAspectRatio(Ogre::Real(2*vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));

    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20, 80, 50);

    //this->game->mWindow->setFullscreen(TRUE, maxW, maxH);
	// Make sure we use the window size as originally requested, NOT the
	// current window size (which may have altered to fit desktop)
	const Ogre::ConfigOptionMap::iterator opti =
			this->game->mRoot->getRenderSystem()->getConfigOptions().find("Video Mode");
	Ogre::StringVector vmopts = Ogre::StringUtil::split(opti->second.currentValue, " x");
	unsigned int w = Ogre::StringConverter::parseUnsignedInt(vmopts[0]);
	unsigned int h = Ogre::StringConverter::parseUnsignedInt(vmopts[1]);
	this->game->mWindow->setFullscreen(!this->game->mWindow->isFullScreen(), w, h);
}

void Immerse::createScene(void)
{
	//
	entGround = mSceneMgr->createEntity("objeto1", "Stair.mesh");
    entGround->setCastShadows(true);

    nodeCursor = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeCursor->setScale(1, 1, 1);
    nodeCursor->attachObject(entGround);
    nodeCursor->setPosition(-4, 6, 05);
    //
	Ogre::Entity* entGround2 = mSceneMgr->createEntity("objeto2", "Stair.mesh");
    entGround2->setCastShadows(true);

    Ogre::SceneNode* nodeCursor2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeCursor2->setScale(1, 1, 1);
    nodeCursor2->attachObject(entGround2);
    nodeCursor2->setPosition(4, -4, 0);
    //
	Ogre::Entity* entGround3 = mSceneMgr->createEntity("objeto3", "Stair.mesh");
    entGround3->setCastShadows(true);

    Ogre::SceneNode* nodeCursor3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeCursor3->setScale(1, 1, 1);
    nodeCursor3->attachObject(entGround3);
    nodeCursor3->setPosition(-5, 5, 03);
}

bool Immerse::mouseMoved(const OIS::MouseEvent &arg)
{
   	mCameraMan->injectMouseMove(arg);
   	mCameraMan2->injectMouseMove(arg);
    return true;
}

bool Immerse::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    mCameraMan->injectMouseDown(arg, id);
    mCameraMan2->injectMouseDown(arg, id);
    return true;
}

bool Immerse::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	mCameraMan->injectMouseUp(arg, id);
	mCameraMan2->injectMouseUp(arg, id);
    return true;
}

bool Immerse::keyPressed( const OIS::KeyEvent &arg )
{
    mCameraMan->injectKeyDown(arg);
    mCameraMan2->injectKeyDown(arg);
    return true;
}

bool Immerse::keyReleased( const OIS::KeyEvent &arg )
{
    mCameraMan->injectKeyUp(arg);
    mCameraMan2->injectKeyUp(arg);
    return true;
}

bool Immerse::draw(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 src = nodeCursor->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion quat = src.getRotationTo(nodeCursor->getPosition());
	nodeCursor->yaw(Ogre::Degree(0.01f));
	//game->mWindow->getViewport(0)->clear(Ogre::FBT_COLOUR | Ogre::FBT_DEPTH, Ogre::ColourValue::Black, 1.0f, 0);
	//game->mWindow->getViewport(1)->clear(Ogre::FBT_COLOUR | Ogre::FBT_DEPTH, Ogre::ColourValue::Black, 1.0f, 0);
	mCameraMan->frameRenderingQueued(evt);
	mCameraMan2->frameRenderingQueued(evt);
    return true;
}

