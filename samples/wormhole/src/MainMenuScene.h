#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

#include <OGRE/Terrain/OgreTerrain.h>
#include <OGRE/Terrain/OgreTerrainGroup.h>

class MainMenuScene : public GAbstractHandler
{
    public:
        MainMenuScene(GBaseClass *base);
        virtual ~MainMenuScene();

        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);
    protected:

        //virtual void createFrameListener(void);
        virtual void destroyScene(void);
        //virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    private:

        Ogre::Camera* mCamera;
        OgreBites::SdkCameraMan* mCameraMan;
        Ogre::Viewport* mViewport;
        CameraSet* cameraSet1;

        Ogre::SceneNode *mCurrentObject;	//pointer to our currently selected object
        //Ogre::RaySceneQuery* mRayScnQuery;	//pointer to our ray scene query

        Ogre::TerrainGlobalOptions* mTerrainGlobals;
        Ogre::TerrainGroup* mTerrainGroup;
        bool mTerrainsImported;

        void defineTerrain(long x, long y);
        void initBlendMaps(Ogre::Terrain* terrain);
        void configureTerrainDefaults(Ogre::Light* light);

        // OIS::KeyListener
        bool keyPressed( const OIS::KeyEvent &arg );
        bool keyReleased( const OIS::KeyEvent &arg );
        // OIS::MouseListener
        bool mouseMoved( const OIS::MouseEvent &arg );
        bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
        bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

        void addToWorld(Ogre::Terrain *terrain);


};

#endif // MAINMENUSCENE_H
