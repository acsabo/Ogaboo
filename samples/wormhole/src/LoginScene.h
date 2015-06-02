#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

class LoginScene : public GAbstractHandler
{
    public:
        LoginScene(GBaseClass *base);
        virtual ~LoginScene();

        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);
        bool keyPressed( const OIS::KeyEvent &arg );

    protected:
    private:
        Ogre::Camera* mCamera;
        OgreBites::SdkCameraMan* mCameraMan;
        unsigned int audioId;
};

#endif // LOGINSCENE_H
