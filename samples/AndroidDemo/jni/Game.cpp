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

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

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
//	    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
//	    {
//	        float x = AMotionEvent_getX(event, 0);
//	        float y = AMotionEvent_getY(event, 0);
//
//	        LOGW("MOTION: x=%d y=%d", (int)x, (int)y);
//
//	        if( abs(x - lastPos.x) < 25)
//	        {
//	        	CameraRot.x += (x - lastPos.x) * 0.01;
//	        }
//
//	        if( abs(y - lastPos.y)< 25)
//	        {
//	        	CameraRot.y += (y - lastPos.y) * 0.01;
//	        }
//
//	        camera->setPosition( cos( CameraRot.x) * 20,  sin( CameraRot.y) * 20 , -sin( CameraRot.x) * 20 );
//	    	camera->lookAt(0,0,0);
//
//	        lastPos.x = x;
//	        lastPos.y = y;
//
//
//	        if(textArea != NULL)
//	        {
//				char text[300];
//				sprintf(text, "X:%d Y:%d", (int)x, (int)y);
//				textArea->setCaption( text );
//	        }
//
//	            /*
//	        	This next big chunk basically sends a raycast straight down from the camera's position
//	        	It then checks to see if it is under world geometry and if it is we move the camera back up
//	        	*/
//	        	//Ogre::Vector3 camPos = camera->getPosition();
//	        	//Ogre::Ray cameraRay(Ogre::Vector3(camPos.x, 5000.0f, camPos.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
//        	    //mRayScnQuery->setRay(cameraRay);
//
//	        	//create a raycast straight out from the camera at the mouse's location
//				Ogre::Ray mouseRay = camera->getCameraToViewportRay( x/float(vp->getActualWidth()),  y/float(vp->getActualHeight()));
//				mRayScnQuery->setRay(mouseRay);
//
//	        	Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
//	        	Ogre::RaySceneQueryResult::iterator iter = result.begin();
//
//	        	if(iter != result.end() && iter->movable)
//	        	{
//	        		LOGW("SELECT: %s", iter->movable->getName().c_str());
//	        	}
//	        	return true;
//
//
//	        return 1;
//	    }
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
	__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "android_main");
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

	__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "android_main 2");

 	game = new Acsabo::Game();
	game->prepare(state);

	__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "android_main 3");

	try { // loop waiting for stuff to do.

		while (true) {

			while ((ident = ALooper_pollAll(0, NULL, &events, (void**) &source))
					>= 0) {
				if (source != NULL) {
					source->process(state, source);

				}

				game->renderOneFrame();

				if (state->destroyRequested != 0) {
					return;
				}
			}

		}

		__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "Game: after go");
	} catch (Ogre::Exception &e) {
		Ogre::StringUtil::StrStreamType msg;
		msg << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__
				<< " DESC: " << e.getFullDescription() << std::endl;
		__android_log_write(ANDROID_LOG_INFO, "DEBUGGING", "Game: erro!");
	}
}
