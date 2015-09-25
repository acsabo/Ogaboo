/*
 * Ogaboo (Open Game Bootstrap) 1.0
 * https://sourceforge.net/projects/ogaboo/
 *
 * Copyright (c) 2014 Adriano de Castro Sabo
 * acsabo@hotmail.com
 *
 * Licensed under http://opensource.org/licenses/MIT
 */

#ifndef GBASECLASS_H
#define GBASECLASS_H

#include <vector>
#include <iostream>
#include <tr1/unordered_map> //boost
using namespace std;

//OGRE
#include <OGRE/Ogre.h>

#include <OGRE/OgrePrerequisites.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreConfigFile.h>
#include "OGRE/OgreFileSystemLayer.h"
#include "OGRE/OgreStaticPluginLoader.h"
#include <OGRE/Plugins/ParticleFX/OgreParticleFXPlugin.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
#include <cpu-features.h>
#include <jni.h>
#include <errno.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <OGRE/RenderSystems/GLES2/OgreGLES2Plugin.h>
#include "OGRE/Android/OgreAPKFileSystemArchive.h"
#include "OGRE/Android/OgreAPKZipArchive.h"
#include <OIS/OISMultiTouch.h>
#endif

//GUI
#include "MYGUI/MyGUI.h"
#include "MYGUI/MyGUI_OgrePlatform.h"

//Theora Video Manager
#include "VideoClipManager.h"
#include "OgreOggSoundManager.h"
#include "OgreOggSoundPlugin.h"

//Load scenes parser
#include "DotSceneLoader.h"

#include "GAbstractHandler.h"

using namespace Ogaboo;

namespace Ogaboo {

    class GBaseClass : public Ogre::FrameListener,
                       public OIS::KeyListener,
						  #if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
						  public OIS::MultiTouchListener,
						  #else
						  public OIS::MouseListener,
						  #endif
                       public Ogre::WindowEventListener
    {
        public:
            class LoadEvent
            {
                public:
                    void beforeLoad();
                    void afterLoad();
            };

            //GAME STATUS
            const static unsigned int GSTATUS_LOADING = 0;
            const static unsigned int GSTATUS_PLAYING = 1;

            GBaseClass();
            virtual ~GBaseClass();

            void addLoadEvent(LoadEvent *evt);
            void addHandler(std::string name, class GAbstractHandler *evt);

            Ogre::Root *mRoot;
            Ogre::RenderWindow* mWindow;
            Ogre::SceneManager* mSceneMgr;

            OgreOggSound::OgreOggSoundManager* mSoundManager;
            Ogaboo::VideoClipManager* videoClipManager;
            CDotScene* mDotScene;

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
            virtual void prepare(struct android_app* state);
            Ogre::GLES2Plugin *g_gles2Plugin = 0;
            virtual void renderOneFrame();
            void setup(struct android_app* state);
#else
            virtual void go();
#endif

            Ogre::ParticleFXPlugin *g_pfxPlugin;
            OgreOggSound::OgreOggSoundPlugin * g_oosPlugin;
            void swapScene();

        protected:
			bool setupDefaultConfigIfNeeded();

            virtual void createFrameListener(void);
            void createScene();
            virtual void destroyScene(void);
            virtual void setupResources(void);
            virtual void createResourceListener(void);
            virtual void loadResources(void);

            // Ogre::FrameListener
            virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

            // OIS::KeyListener
            virtual bool keyPressed( const OIS::KeyEvent &arg );
            virtual bool keyReleased( const OIS::KeyEvent &arg );

			#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
            // OIS::MultiTouchListener
			virtual bool touchMoved( const OIS::MultiTouchEvent &arg );
			virtual bool touchPressed( const OIS::MultiTouchEvent &arg );
			virtual bool touchReleased( const OIS::MultiTouchEvent &arg );
			virtual bool touchCancelled( const OIS::MultiTouchEvent &arg );
			Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName);
			void loadResources(const char *name);
			#else
			virtual bool configure();
            // OIS::MouseListener
            virtual bool mouseMoved( const OIS::MouseEvent &arg );
            virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
            virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			#endif
            //Adjust mouse clipping area
            virtual void windowResized(Ogre::RenderWindow* rw);
            //Unattach OIS before window shutdown (very important under Linux)
            virtual void windowClosed(Ogre::RenderWindow* rw);

            bool setCurrentHandler(std::string name);
        protected:

            tr1::unordered_map<std::string, GAbstractHandler*> mHandlers;
            GAbstractHandler* mCurrentHandler;

        private:

            MyGUI::Gui* mGUI;
            MyGUI::OgrePlatform* mPlatform;

            Ogre::String mResourcesCfg;
            Ogre::String mPluginsCfg;
            virtual bool init();

            // was cursor visible before dialog appeared
            bool mCursorWasVisible;
            bool mShutDown;

            // File system abstraction layer
        	Ogre::FileSystemLayer* mFSLayer;

            //OIS Input devices
            OIS::InputManager* mInputManager;
        	//Fix for 1.9:
        	OgreBites::InputContext mInputContext;

			#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
            OIS::MultiTouch* mMouse;
            // Android asset manager to access files inside apk
        	AAssetManager* mAssetMgr;
			#else
			OIS::Mouse*    mMouse;
			#endif
            OIS::Keyboard* mKeyboard;

            unsigned int mStatus;
            std::vector <class LoadEvent *> mLoadEvents;
    };
}
#endif // GBASECLASS_H
