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
    mCamera->setNearClipDistance(5);

    // Create the camera 2
    Ogre::Camera* mCamera2 = mSceneMgr->createCamera("PlayerCam2");
    // Position it at 500 in Z direction
    mCamera2->setPosition(Ogre::Vector3(15,15,15));

    // Look back along -Z
    mCamera2->lookAt(Ogre::Vector3(0,0,0));
    mCamera2->setNearClipDistance(5);

    // Position it at 500 in Z direction
    mCamera2->setPosition(Ogre::Vector3(25,15,15));

    // Look back along -Z
    mCamera2->lookAt(Ogre::Vector3(0,0,0));
    mCamera2->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    // Create one viewport, entire window
    Ogre::Viewport* vp = this->game->mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue::Blue);
    vp->setDimensions(0,0,0.5,1);

    Ogre::Viewport* vp2 = this->game->mWindow->addViewport(mCamera2, 1);
    vp2->setBackgroundColour(Ogre::ColourValue::Green);
    vp2->setDimensions(0.5,0,0.5,1);


    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mCamera2->setAspectRatio(Ogre::Real(vp2->getActualWidth()) / Ogre::Real(vp2->getActualHeight()));
}

void Immerse::createScene(void)
{
}

bool Immerse::draw(const Ogre::FrameEvent& evt)
{
	game->mWindow->getViewport(0)->clear(Ogre::FBT_COLOUR | Ogre::FBT_DEPTH, Ogre::ColourValue::Blue, 1.0f, 0);
	game->mWindow->getViewport(1)->clear(Ogre::FBT_COLOUR | Ogre::FBT_DEPTH, Ogre::ColourValue::Green, 1.0f, 0);
    return true;
}

