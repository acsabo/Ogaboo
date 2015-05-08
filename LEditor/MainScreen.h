#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

using namespace Acsabo;

class MainScreen : public GAbstractHandler
{
    public:
        MainScreen(GBaseClass *base);
        virtual ~MainScreen();

        //overriden methods
        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);

        virtual bool mouseMoved(const OIS::MouseEvent &arg);// { return true; }
        virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);// { return true; }
        virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);// { return true; }

        // OIS::KeyListener
        bool keyPressed( const OIS::KeyEvent &arg );
        bool keyReleased( const OIS::KeyEvent &arg );

    protected:
        //Ogre::Plane mGridPlane;
        Ogre::SceneNode *mCurrentObject;
        Ogre::SceneNode* nodeCursor;
        Ogre::SceneNode* mGridPlane;

        bool addObjectAt(Ogre::Vector3 position);
        bool removeObjectAt(Ogre::Vector3 position);
        Ogre::String getKey(Ogre::Vector3 position);

        bool quit(const CEGUI::EventArgs &e);
        bool load(const CEGUI::EventArgs &e);
        bool save(const CEGUI::EventArgs &e);
        bool physics(const CEGUI::EventArgs &e);
        bool OnMouseClick_ItemListbox(const CEGUI::EventArgs& e);
};

#endif // MAINSCREEN_H
