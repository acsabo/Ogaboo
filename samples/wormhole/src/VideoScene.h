#ifndef VIDEOSCENE_H
#define VIDEOSCENE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

using namespace Ogaboo;

class VideoScene : public GAbstractHandler
{
    public:
        VideoScene();
        ~VideoScene();

        void setup(const Ogaboo::GBaseClass* base);
        void load(const Ogaboo::GBaseClass* base);
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

    	bool mouseMoved(const OIS::MouseEvent &arg);
    	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    	// OIS::KeyListener
    	bool keyPressed(const OIS::KeyEvent &arg);
    	bool keyReleased(const OIS::KeyEvent &arg);

        Ogre::Camera* mCamera;
        OgreBites::SdkCameraMan* mCameraMan;
        Ogre::Viewport* mViewport;
        CameraSet* cameraSet1;

        TheoraVideoClip* clip;


};

#endif // VIDEOSCENE_H
