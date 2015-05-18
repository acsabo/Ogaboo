#include "MainScene.h"
#include <iostream>

MainScene::MainScene(GBaseClass *base) : GAbstractHandler(base, true)
{
    //ctor
}

MainScene::~MainScene()
{
    //dtor
}

void MainScene::setup(void)
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

    // Create one viewport, entire window
    Ogre::Viewport* vp = this->game->mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

}

void MainScene::createScene(void)
{
    //ver flag acima
    game->mDotScene->parseDotScene("terrain01.scene","General",mSceneMgr);
}

    //Ogre::Vector3 m_rotation_pivot = Ogre::Vector3(10,15,10);
    //Ogre::Vector3 m_delta_movement = Ogre::Vector3(0.00f,0.001f,0.00f);

bool MainScene::draw(const Ogre::FrameEvent& evt)
{
    /*
    Ogre::Vector3 camera_x_axis = mCamera->getDerivedRight();
    Ogre::Vector3 camera_y_axis = mCamera->getDerivedUp();

    // Calculate the rotation radius
    float rotation_radius = (mCamera->getDerivedPosition() - m_rotation_pivot).length();

    // First move the camera to the rotation pivot
    mCamera->setPosition(m_rotation_pivot);

    Ogre::Quaternion current_camera_rotation = mCamera->getDerivedOrientation();

    if(m_delta_movement.x != 0.0f)
    {
       // Use the x movement to perform yaw around the camera_y_axis
       Ogre::Quaternion yaw_delta_rotation(Ogre::Radian(m_delta_movement.x), camera_y_axis);

       // Add this delta rotation to the current rotation
       current_camera_rotation = current_camera_rotation * yaw_delta_rotation;
    }
    if(m_delta_movement.y != 0.0f)
    {
       // Use the y movement to perform pitch around the camera_x_axis
       Ogre::Quaternion pitch_delta_rotation(Ogre::Radian(m_delta_movement.y), camera_x_axis);

       // Add this delta rotation to the current camera rotation
       current_camera_rotation = current_camera_rotation * pitch_delta_rotation;
    }

    // Set the new orientation for the camera
    mCamera->setOrientation(current_camera_rotation);

    // Once the rotation is done move the camera back in the camera's direction by the radius
    Ogre::Vector3 camera_offset = mCamera->getDerivedDirection() * (-rotation_radius);
    mCamera->setPosition(m_rotation_pivot + camera_offset);
    //mCamera->lookAt(Ogre::Vector3(0,0,0));
*/
    return true;
}

