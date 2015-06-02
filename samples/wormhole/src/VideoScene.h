#ifndef VIDEOSCENE_H
#define VIDEOSCENE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

using namespace Ogaboo;

class VideoScene : public GAbstractHandler
{
    public:
        VideoScene(GBaseClass *base);
        ~VideoScene();

        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);

        void onShow(void){
        	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::onShow --- ***", Ogre::LML_NORMAL);
        	clip->play();
        };
        void onHide(void){
        	Ogre::LogManager::getSingleton().logMessage("*** --- VideoScene::onHide --- ***", Ogre::LML_NORMAL);
        	clip->pause();
        };

    private:
        Ogre::Camera* mCamera;
        OgreBites::SdkCameraMan* mCameraMan;
        Ogre::Viewport* mViewport;
        CameraSet* cameraSet1;

        TheoraVideoClip* clip;


};

#endif // VIDEOSCENE_H
