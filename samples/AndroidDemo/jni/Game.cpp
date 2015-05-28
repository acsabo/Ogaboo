/*
 * Game.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: Adriano
 */

#include "Game.h"
#include <iostream>

#include <jni.h>
#include <errno.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <OGRE/OgreString.h>

using namespace std;
using namespace Acsabo;

namespace Acsabo {

Game::Game() {
	mainScene = new MainScene(this);
}

Game::~Game() {
	delete mainScene;
}

}

class AppState {
public:
	int CurentState;
};

class NativeApp {

public:
	struct android_app* app;

	ASensorManager* sensorManager;
	ASensorEventQueue* sensorEventQueue;

	AppState state;
};

NativeApp app;

Acsabo::Game* game;

static int32_t handleInput(struct android_app* app, AInputEvent* event) {

	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "*** Game::handleInput ***");
		//ANativeActivity_finish();
	}

	return 0;
}

static void handleCmd(struct android_app* app, int32_t cmd) {
	switch (cmd) {
	case APP_CMD_SAVE_STATE:
		// http://developer.android.com/reference/android/app/NativeActivity.html
		break;
	case APP_CMD_INIT_WINDOW:
		__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "handleCmd");
        	game->setup(app);
//            if(app->window && gRoot)
//            {
//                AConfiguration* config = AConfiguration_new();
//                AConfiguration_fromAssetManager(config, app->activity->assetManager);
//                gAssetMgr = app->activity->assetManager;
//
//                if(!gRenderWnd)
//                {
//				    Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(app->activity->assetManager) );
//					Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(app->activity->assetManager) );
//
//                    Ogre::NameValuePairList opt;
//                    opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)app->window);
//                    opt["androidConfig"] = Ogre::StringConverter::toString((int)config);
//
//					gRenderWnd = gRoot->createRenderWindow("OgreWindow", 0, 0, false, &opt);
//
//					InitStartScene();
//                }
//                else
//                {
//					static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(app->window, config);
//                }
//                AConfiguration_delete(config);
//            }
		break;
	case APP_CMD_TERM_WINDOW:
//            if(gRoot && gRenderWnd)
//				static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
		break;
	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.

		break;
	case APP_CMD_LOST_FOCUS:
		// Also stop animating.
		break;
	}
}

void android_main(struct android_app* state) {
	app_dummy();
	state->userData = &app;

	// Prepare to monitor accelerometer
	app.sensorManager = ASensorManager_getInstance();
	app.sensorEventQueue = ASensorManager_createEventQueue(app.sensorManager,
			state->looper, LOOPER_ID_USER, NULL, NULL);

	if (state->savedState != NULL) {
		// We are starting with a previous saved state; restore from it.
		app.state = *(AppState*) state->savedState;
	}

	state->onAppCmd = &handleCmd;
	state->onInputEvent = &handleInput;

	int ident, events;
	struct android_poll_source* source;

 	game = new Acsabo::Game();
	game->prepare(state);

	try { // loop waiting for stuff to do.
		while (true) {

			while ((ident = ALooper_pollAll(0, NULL, &events, (void**) &source))
					>= 0) {
				if (source != NULL) {
					source->process(state, source);
					__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "Game: cccc");
				}
				__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "Game: dddd");


				if (state->destroyRequested != 0) {
					return;
				}
			}
			game->renderOneFrame();

		}

		__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "Game: after go");
	} catch (Ogre::Exception &e) {
		Ogre::StringUtil::StrStreamType msg;
		msg << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__
				<< " DESC: " << e.getFullDescription() << std::endl;
		__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "Game: erro!");
	}
}
