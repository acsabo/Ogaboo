#include "VideoScene.h"

using namespace Ogaboo;

VideoScene::VideoScene(GBaseClass *base) : GAbstractHandler(base, true)
{
	cameraSet1 = new Camera_Set();
    //ctor
}

VideoScene::~VideoScene()
{
    //dtor
}

void VideoScene::setup(void)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::setup  --- ***", Ogre::LML_NORMAL);

    // Get the SceneManager, in this case a generic one
    mSceneMgr = this->game->mRoot->createSceneManager(Ogre::ST_GENERIC);

    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(200,200,400));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    cameraSet1->mCamera = mCamera;
    cameraSet1->mCameraMan = mCameraMan;
//    cameraSet1->mViewport = mViewport;

    this->addCameraSet(cameraSet1);
	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::setup 1 --- ***", Ogre::LML_NORMAL);

    // Create one viewport, entire window
    mViewport = this->game->mWindow->addViewport(mCamera, 1);
	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::setup 2 --- ***", Ogre::LML_NORMAL);

    mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::setup 3 --- ***", Ogre::LML_NORMAL);

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));

    Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::setup end --- ***", Ogre::LML_NORMAL);
 }

void VideoScene::createScene(void)
{
    //loag video
    clip = this->game->videoClipManager->load ("bunny.ogg", "video_material");

    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

    Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane, 400, 360, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);

    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    Ogre::SceneNode* planeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    planeNode->attachObject(entGround);
    entGround->setMaterialName("video_material");
    entGround->setCastShadows(false);
    planeNode->setPosition(Ogre::Vector3(0,0,0));

/*
    //------------Create Sounds
    //Load sounds fot the menu
    this->game->mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    // Create a streamed sound, no looping, no prebuffering
    this->game->mSoundManager->createSound("Sound1", "bunny.ogg", false, true, false);

    this->game->mSoundManager->getSound("Sound1")->play();
*/
}

bool VideoScene::draw(const Ogre::FrameEvent& evt)
{
	mCameraMan->frameRenderingQueued(evt);
//	this->game->mSoundManager->getSound("Sound1")->setPosition(mCameraMan->getCamera()->getPosition());
 //   if (clip->isDone()) this->kill();
    this->game->videoClipManager->draw(evt);
    return true;
}

