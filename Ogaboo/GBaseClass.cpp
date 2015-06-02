/*
 * Ogaboo (Open Game Bootstrap) 1.0
 * https://sourceforge.net/projects/ogaboo/
 *
 * Copyright (c) 2014 Adriano de Castro Sabo
 * acsabo@hotmail.com
 *
 * Licensed under http://opensource.org/licenses/MIT
 */

#include "GBaseClass.h"
#include <exception>

#include <iostream> //remove this
#include "OGRE/OgreStaticPluginLoader.h"
#include <OGRE/OgreCommon.h>

using namespace std;

using namespace Ogaboo;

int currentHandler = 0;

GBaseClass::GBaseClass()
    : mRoot(0),
      mWindow(0),
      mResourcesCfg(Ogre::StringUtil::BLANK),
      mPluginsCfg(Ogre::StringUtil::BLANK),
      mCursorWasVisible(false),
      mShutDown(false),
      mInputManager(0),
      mMouse(0),
      mKeyboard(0)
{
/*
    //Init bullet world
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
*/
}

GBaseClass::~GBaseClass()
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
    delete videoClipManager;
    delete mSoundManager;
}

void GBaseClass::addHandler(Ogaboo::GAbstractHandler *handler)
{
    this->GAHandlers.push_back(handler);
}

//-------------------------------------------------------------------------------------
void GBaseClass::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** createFrameListener 1 ***");
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

	//Fix for 1.9
	mInputContext.mKeyboard = mKeyboard;
	mInputContext.mMouse = mMouse;

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

#endif

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
    mRoot->addFrameListener(this);

	Ogre::LogManager::getSingleton().logMessage("*** ---  createFrameListener  --- ***", Ogre::LML_NORMAL);
    //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createFrameListener end ***");
}
//-------------------------------------------------------------------------------------
void GBaseClass::destroyScene(void)
{
}

//-------------------------------------------------------------------------------------


void GBaseClass::createScene(void)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- GBaseClass::createScene  --- ***", Ogre::LML_NORMAL);
	//__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createScene 1 ***");

	mDotScene = new CDotScene();

	#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
		//INICIA O CEGUI para todas as Scenes
		mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(); //create(*mWindow);
	#endif

	//__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createScene 2 ***");

    // set the default resource groups to be used
//    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
//    CEGUI::Font::setDefaultResourceGroup("fonts");
//    CEGUI::Scheme::setDefaultResourceGroup("schemes");
//    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
//    CEGUI::WindowManager::setDefaultResourceGroup("layouts");

//	//__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createScene 3+ ***");
//
//    // load scheme and set up defaults
//	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	Ogre::LogManager::getSingleton().logMessage("*** --- GBaseClass::createScene2  --- ***", Ogre::LML_NORMAL);

    //Init Sound API
    mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createScene 36 ***");
    if (!mSoundManager->init())
    {
    	//__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** OgreOggSound : Init error. No sound device ***");
        Ogre::LogManager::getSingletonPtr()->logMessage("*** OgreOggSound : Init error. No sound device ***");
    }
	Ogre::LogManager::getSingleton().logMessage("*** --- GBaseClass::createScene3  --- ***", Ogre::LML_NORMAL);

    //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createScene 37 ***");
    //Init Video API (passing the sound device)
    videoClipManager = new VideoClipManager(mSoundManager);
    //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createScene 38 ***");
	Ogre::LogManager::getSingleton().logMessage("*** --- GBaseClass::createScene4  --- ***", Ogre::LML_NORMAL);

	for (unsigned int i = 0; i < GAHandlers.size(); i++)
	{
		if (GAHandlers[i]->getAutoCreateScene())
		{
			GAHandlers[i]->createScene();
		}
	}
    //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::createScene end ***");
	Ogre::LogManager::getSingleton().logMessage("*** ---  GBaseClass::createScene  --- ***", Ogre::LML_NORMAL);
}


//-------------------------------------------------------------------------------------

/**
Opens the APK file to access files within.
*/

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
Ogre::DataStreamPtr GBaseClass::openAPKFile(const Ogre::String& fileName)
{
	Ogre::DataStreamPtr stream;
	AAsset* asset = AAssetManager_open(mAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
	if(asset)
	{
		off_t length = AAsset_getLength(asset);
		void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
		memcpy(membuf, AAsset_getBuffer(asset), length);
		AAsset_close(asset);

		stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
	}
	return stream;
}

void GBaseClass::loadResources(const char *name)
{
	Ogre::ConfigFile cf;
	cf.load(openAPKFile(name));

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	while (seci.hasMoreElements())
	{
		Ogre::String sec, type, arch;
		sec = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}
}

void GBaseClass::prepare(struct android_app* state)
{
    this->status = GSTATUS_LOADING;
    mFSLayer = OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);

	mAssetMgr = state->activity->assetManager;
//	Ogre::FileSystemLayer* mFSLayer;

//	mFSLayer = OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);

//	//C:\MinGW\msys\1.0\home\a.sabo\cegui_android\samples\browser\include
//	//CEGuiOgreBaseApplication.cpp !!! ver aqui !!!
	mRoot = new Ogre::Root();//"", "", ""); //this is needed to avoid looking for plugins.cfg

	// Register the ES2 plugin
	g_gles2Plugin = OGRE_NEW Ogre::GLES2Plugin();
	Ogre::Root::getSingleton().installPlugin(g_gles2Plugin);

	// Register particle plugin
	g_pfxPlugin = OGRE_NEW Ogre::ParticleFXPlugin();
	Ogre::Root::getSingleton().installPlugin(g_pfxPlugin);

	// Register the OgreOggSound plugin
	g_oosPlugin = OGRE_NEW OgreOggSound::OgreOggSoundPlugin();
	Ogre::Root::getSingleton().installPlugin(g_oosPlugin);

	//setupDefaultConfigIfNeeded();

	// Grab the available render systems
	const Ogre::RenderSystemList &renderSystemList = mRoot->getAvailableRenderers();

	if(renderSystemList.empty())
	{
		 __android_log_print(ANDROID_LOG_ERROR, "DEBUGGING", "+++ renderSystemList.empty()");
		return;

	}
    mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
	mRoot->initialise(false);
	//__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::prepare end ***");

}

void GBaseClass::setup(struct android_app* state)
{
	Ogre::ArchiveManager::getSingleton().addArchiveFactory(new Ogre::APKFileSystemArchiveFactory(mAssetMgr));
	Ogre::ArchiveManager::getSingleton().addArchiveFactory(new Ogre::APKZipArchiveFactory(mAssetMgr));

	   Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();

	   //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::setup 2 ***");


	   AConfiguration* config = AConfiguration_new();
	   AConfiguration_fromAssetManager(config, state->activity->assetManager);

	   //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::setup 3 ***");

	   Ogre::NameValuePairList opt;
	   opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)state->window);
	   opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

		mWindow	= mRoot->createRenderWindow("OgreWindow", 0, 0, false, &opt);

   //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::setup 4 ***");

   if (!init())
       return;

   for (unsigned int i = 0; i < GAHandlers.size(); i++)
   {
        GAHandlers[i]->setup();
   }

   //create Scene of each handler
   createScene();

   createFrameListener();
   //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::setup end ***");
}
#endif

void GBaseClass::setupResources(void)
{
	//__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::setupResources ***");
   //Adr
   for (unsigned int i = 0; i < loadEvents.size(); i++)
        loadEvents[i]->beforeLoad();

   //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::setupResources 2 ***");

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
   loadResources("resources.cfg");
#else
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
#endif

    //Adr
    for (unsigned int i = 0; i < loadEvents.size(); i++)
        loadEvents[i]->afterLoad();

    //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::setupResources end ***");
}
//-------------------------------------------------------------------------------------
void GBaseClass::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void GBaseClass::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
/*
void GBaseClass::setupDefaultConfigIfNeeded()
{
    // Check if the config exists
    bool success = mRoot->restoreConfig();

    if (!success)
    {
        // If not we set our default values for all renderers if possible
        const Ogre::RenderSystemList& renderSystems = mRoot->getAvailableRenderers();

        size_t renderSystemCount = renderSystems.size();
        for(size_t i = 0; i < renderSystemCount; ++i)
        {
            Ogre::RenderSystem* currentRenderSys = renderSystems.at(i);
            Ogre::ConfigOptionMap& configOptions = currentRenderSys->getConfigOptions();
            Ogre::ConfigOptionMap::iterator foundConfigIter;

            foundConfigIter = configOptions.find("Full Screen");
            if (foundConfigIter != configOptions.end())
                currentRenderSys->setConfigOption("Full Screen","No");

            foundConfigIter = configOptions.find("Video Mode");
            if (foundConfigIter != configOptions.end())
            {
                Ogre::StringVector::iterator optionsIterCur = foundConfigIter->second.possibleValues.begin();
                Ogre::StringVector::iterator optionsIterEnd = foundConfigIter->second.possibleValues.end();
                while(optionsIterCur != optionsIterEnd)
                {
                    if (optionsIterCur->compare("1280 x 768 @ 32-bit colour") == 0)
                    {
                        currentRenderSys->setConfigOption("Video Mode", *optionsIterCur);
                        break;
                    }
                    ++optionsIterCur;
                }
                if (optionsIterCur == optionsIterEnd)
                {
                    optionsIterCur = foundConfigIter->second.possibleValues.begin();
                    while(optionsIterCur != optionsIterEnd)
                    {
                        if (optionsIterCur->compare(0, 10, "1280 x 768") == 0)
                        {
                            currentRenderSys->setConfigOption("Video Mode", *optionsIterCur);
                            break;
                        }
                        ++optionsIterCur;
                    }
                }
            }
        }
    }
    //__android_log_print(ANDROID_LOG_INFO, "DEBUGGING", "+++ setupDefaultConfigIfNeeded end ");
}
*/
//-------------------------------------------------------------------------------------
bool GBaseClass::init(void)
{
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    mRoot = new Ogre::Root(mPluginsCfg);
#endif

    setupResources();

#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    bool carryOn = configure();
    if (!carryOn) return false;
    //create manager/camera and viewport for each registered handler
    for (unsigned int i = 0; i < GAHandlers.size(); i++)
    {
    	 mWindow->removeAllViewports();
         GAHandlers[i]->setup();
    }
#endif

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();

    // Load resources
    loadResources();

    Ogre::LogManager::getSingleton().logMessage("*** ---  GBaseClass::init DONE --- ***", Ogre::LML_NORMAL);
    //__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::init end ***");
    return true;
};
//-------------------------------------------------------------------------------------
bool GBaseClass::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
//	Ogre::LogManager::getSingleton().logMessage("*** ---  frameRenderingQueued --- ***", Ogre::LML_NORMAL);
    if(mWindow->isClosed())
        return false;
    if(mShutDown)
        return false;

#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    //Need to capture/update each device
//    mKeyboard->capture();
 //   mMouse->capture();
    mInputContext.capture();
    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
#endif
    GAHandlers[currentHandler]->draw(evt);

//    if (!GAHandlers[currentHandler]->isAlive())
//    {
//        //mWindow->getViewport(0)->clear(Ogre::FBT_COLOUR | Ogre::FBT_DEPTH, Ogre::ColourValue::Black, 1.0f, 0);
//    	Ogre::LogManager::getSingleton().logMessage("*** ---  frameRenderingQueued!!! --- ***", Ogre::LML_NORMAL);
//        currentHandler++;
//        GAHandlers[currentHandler]->createScene();
//    }

    ////__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::frameRenderingQueued end ***");
    return true;
}
//-------------------------------------------------------------------------------------
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}
#endif

bool GBaseClass::keyPressed( const OIS::KeyEvent &arg )
{
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(static_cast<int>(arg.key)));
    CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(arg.key);
#endif

    //CEGUI::System &sys = CEGUI::System::getSingleton();
    //CEGUI::GUIContext::injectKeyDown(arg.key);
    //CEGUI::GUIContext::injectChar(arg.key);

    bool result = GAHandlers[currentHandler]->keyPressed(arg);
    if (result && arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    return result;
}

bool GBaseClass::keyReleased( const OIS::KeyEvent &arg )
{
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(static_cast<int>(arg.key)));
    CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(arg.key);
#endif

    //CEGUI::System &sys = CEGUI::System::getSingleton();
    //sys.injectKeyDown(arg.key);
    //sys.injectChar(arg.text);

    //return currentManager.keyReleased
    return GAHandlers[currentHandler]->keyReleased(arg);
}

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
bool GBaseClass::touchMoved( const OIS::MultiTouchEvent &arg )
{
//    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);

    //CEGUI::System &sys = CEGUI::System::getSingleton();
    //sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    // Scroll wheel.
    if (arg.state.Z.rel){
	
        //sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
//        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	}
    //return currentManager.mouseMoved
    bool result = GAHandlers[currentHandler]->touchMoved(arg);
    return true;
}

bool GBaseClass::touchPressed( const OIS::MultiTouchEvent &arg)
{
//    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));

    bool result = GAHandlers[currentHandler]->touchPressed(arg);
    //return currentManager.mousePressed
    return true;
}

bool GBaseClass::touchReleased( const OIS::MultiTouchEvent &arg)
{
//    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));

    bool result = GAHandlers[currentHandler]->touchReleased(arg);
    //return currentManager.mouseReleased
    return true;
}

bool GBaseClass::touchCancelled( const OIS::MultiTouchEvent &arg )
{
	return false;//???????????
}

void GBaseClass::renderOneFrame()
{
	//__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** GBaseClass::renderOneFrame END ***");

    // Pump window messages for nice behaviour
    Ogre::WindowEventUtilities::messagePump();
	mRoot->renderOneFrame();

}
#else

void GBaseClass::go()
{
#ifdef _DEBUG
    mResourcesCfg = "resources/resources_d.cfg";
    mPluginsCfg = "resources/plugins_d.cfg";
#else
    mResourcesCfg = "resources/resources.cfg";
    mPluginsCfg = "resources/plugins.cfg";
#endif

    if (!init())
        return;

    //create Scene of each handler
    createScene();

    createFrameListener();

    Ogre::LogManager::getSingleton().logMessage("*** ---  go() --- ***", Ogre::LML_NORMAL);

	//Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(mRoot->getDefaultMinPixelSize()), Ogre::LML_NORMAL);

    mWindow->removeAllViewports();
    mRoot->startRendering();

    // clean up
    destroyScene();
}

bool GBaseClass::mouseMoved( const OIS::MouseEvent &arg )
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);

    //CEGUI::System &sys = CEGUI::System::getSingleton();
    //sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    // Scroll wheel.
    if (arg.state.Z.rel)
    {
        //sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(arg.state.Z.rel / 120.0f);
    }
    //return currentManager.mouseMoved
    GAHandlers[currentHandler]->mouseMoved(arg);
    return true;
}

bool GBaseClass::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));

    //return currentManager.mousePressed
    GAHandlers[currentHandler]->mousePressed(arg, id);
    return true;
}

bool GBaseClass::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));

    //return currentManager.mouseReleased
    GAHandlers[currentHandler]->mouseReleased(arg, id);
    return true;
}

bool GBaseClass::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
//   	if(manualInitialize("OpenGL"))
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
    	Ogre::LogManager::getSingleton().logMessage("*** ---  mRoot->initialise --- ***", Ogre::LML_NORMAL);
        return true;
    }
    else
    {
    	Ogre::LogManager::getSingleton().logMessage("*** ---  not showConfigDialog --- ***", Ogre::LML_NORMAL);
        return false;
    }
}

#endif

//Adjust mouse clipping area
void GBaseClass::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

	#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
	#endif
}

//Unattach OIS before window shutdown (very important under Linux)
void GBaseClass::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

//--- adr
void GBaseClass::addLoadEvent(LoadEvent*evt) {
    loadEvents.push_back(evt);
}

void GBaseClass::LoadEvent::beforeLoad()
{
    cout << "beforeLoad" << endl;
}

void GBaseClass::LoadEvent::afterLoad()
{
    cout << "afterLoad" << endl;
}

void GBaseClass::nextGAHandler()
{
	if (currentHandler < (int)(GAHandlers.size() -1))
	{
		currentHandler++;
		swapSceneMgr(currentHandler);
	}
}

void GBaseClass::priorGAHandler()
{
	if (currentHandler > 0)
	{
		currentHandler--;
		swapSceneMgr(currentHandler);
	}
}

void GBaseClass::swapSceneMgr(unsigned short index)
{
	if (index >= 0 && index < GAHandlers.size())
	{
		GAHandlers[currentHandler]->onHide();
		Ogre::LogManager::getSingleton().logMessage("*** --- GBaseClass::swapSceneMgr1  --- ***", Ogre::LML_NORMAL);
		currentHandler = index;
		mWindow->removeAllViewports();

		Ogre::Camera *cam = GAHandlers[currentHandler]->getCameraSet()->mCamera;
		Ogre::Viewport *vp = mWindow->addViewport(cam);//GAHandlers[currentHandler]->getCameraSet()->mViewport;

		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
		cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		GAHandlers[currentHandler]->onShow();
		Ogre::LogManager::getSingleton().logMessage("*** --- GBaseClass::swapSceneMgr2 end.  --- ***", Ogre::LML_NORMAL);

	}
}
