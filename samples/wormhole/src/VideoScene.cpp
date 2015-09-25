#include "VideoScene.h"

using namespace Ogaboo;

VideoScene::VideoScene() : GAbstractHandler("videoScene")
{
	cameraSet1 = new Camera_Set();
    //ctor
}

VideoScene::~VideoScene()
{
    //dtor
}

const Ogaboo::GBaseClass* game;

void VideoScene::setup(const Ogaboo::GBaseClass* base)
{
	game = base;
	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::setup  --- ***", Ogre::LML_NORMAL);

    mSceneMgr = base->mRoot->createSceneManager(Ogre::ST_GENERIC);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(200,200,400));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    cameraSet1->mCamera = mCamera;

    this->addCameraSet(cameraSet1);
}

void VideoScene::load(const Ogaboo::GBaseClass* base)
{

	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::load --- ***", Ogre::LML_NORMAL);
    //loag video

    clip = game->videoClipManager->load ("bunny.ogg", "video_material");

    Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, 400, 360, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    Ogre::SceneNode* planeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    planeNode->attachObject(entGround);
    entGround->setMaterialName("video_material");
    entGround->setCastShadows(false);

    Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::load end--- ***", Ogre::LML_NORMAL);
}
bool VideoScene::draw(const Ogre::FrameEvent& evt)
{
	mCameraMan->frameRenderingQueued(evt);
	game->videoClipManager->draw(evt);
    return true;
}

bool VideoScene::mouseMoved(const OIS::MouseEvent &arg)
{
	mCameraMan->injectMouseMove(arg);
    return true;
}

bool VideoScene::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool VideoScene::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	mCameraMan->injectMouseUp(arg, id);
    return true;
}

bool VideoScene::keyPressed( const OIS::KeyEvent &arg )
{
	mCameraMan->injectKeyDown(arg);
    return true;
}

bool VideoScene::keyReleased( const OIS::KeyEvent &arg )
{
	mCameraMan->injectKeyUp(arg);
    return true;
}

