#ifndef IMMERSE_H
#define IMMERSE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

class Immerse : public GAbstractHandler
{
    public:
		Immerse();
        virtual ~Immerse();

        void setup(const Ogaboo::GBaseClass &base);
        bool draw(const Ogre::FrameEvent& evt);

        bool mouseMoved(const OIS::MouseEvent &arg);
        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

        bool keyPressed( const OIS::KeyEvent &arg );
        bool keyReleased( const OIS::KeyEvent &arg );
    protected:
    private:
        Ogre::Camera* mCamera;
        Ogre::Camera* mCamera2;
        OgreBites::SdkCameraMan* mCameraMan;
        OgreBites::SdkCameraMan* mCameraMan2;
};

#endif // IMMERSE_H
