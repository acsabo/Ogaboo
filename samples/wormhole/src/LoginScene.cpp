#include "LoginScene.h"

LoginScene::LoginScene(GBaseClass *base) : GAbstractHandler(base, true)
{
    //ctor
}

LoginScene::~LoginScene()
{
    //dtor
}

void LoginScene::setup(void)
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

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);


}

bool okAction(const CEGUI::EventArgs &e)
{
    //Load sounds fot the menu
    OgreOggSound::OgreOggSoundManager* mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    // Create a streamed sound, no looping, no prebuffering
    mSoundManager->getSound("Sound1")->play();

    return true;
}

void LoginScene::createScene(void)
{
	std::cout << "createScene" << std::endl;
	CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("GameMenu.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(layout);
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    //Load sounds fot the menu
    OgreOggSound::OgreOggSoundManager* mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    // Create a streamed sound, no looping, no prebuffering
    mSoundManager->createSound("Sound1", "test.ogg", true, false, false);

    mSoundManager->getSound("Sound1")->play();

}

bool LoginScene::draw(const Ogre::FrameEvent& evt)
{
    return true;
}

bool LoginScene::keyPressed( const OIS::KeyEvent &arg )
{
    if (arg.key == OIS::KC_B)
    {
        OgreOggSound::OgreOggSoundManager* mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();

        mSoundManager->getSound("Sound1")->play();

    }
    GAbstractHandler::keyPressed(arg);

    return true;
}
