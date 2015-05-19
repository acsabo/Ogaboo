#ifndef IMMERSE_H
#define IMMERSE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

class Immerse : public GAbstractHandler
{
    public:
		Immerse(GBaseClass *base);
        virtual ~Immerse();

        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);

        bool mouseMoved(const OIS::MouseEvent &arg);
        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

        bool keyPressed( const OIS::KeyEvent &arg );
        bool keyReleased( const OIS::KeyEvent &arg );
    protected:
    private:
};

#endif // IMMERSE_H
