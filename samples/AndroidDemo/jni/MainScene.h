/*
 * MainScene.h
 *
 *  Created on: Jul 9, 2014
 *      Author: Adriano
 */

#ifndef MAINSCENE_H_
#define MAINSCENE_H_

#include <GBaseClass.h>
#include <GAbstractHandler.h>
#include "GObj.h"

namespace Acsabo {

class MainScene : public GAbstractHandler{
public:
    MainScene(GBaseClass *base);
    virtual ~MainScene();

    void setup(void);
    void createScene(void);
    bool draw(const Ogre::FrameEvent& evt);

    Ogre::SceneNode* addObject(const std::string name, GObj* obj);
    bool keyPressed( const OIS::KeyEvent &arg );


    /*-----------------------------------------------------------------------------
    | Initialize the RT Shader system.
    -----------------------------------------------------------------------------*/
    Ogre::RTShader::ShaderGenerator*			mShaderGenerator;			// The Shader generator instance.
	ShaderGeneratorTechniqueResolverListener*	mMaterialMgrListener;		// Shader generator material manager listener.
    virtual bool initialiseRTShaderSystem(Ogre::SceneManager* sceneMgr)
    {
    	if (Ogre::RTShader::ShaderGenerator::initialize())
    	{
    		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

    		mShaderGenerator->addSceneManager(sceneMgr);

    #if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID && OGRE_PLATFORM != OGRE_PLATFORM_NACL && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
    		// Setup core libraries and shader cache path.
    		Ogre::StringVector groupVector = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
    		Ogre::StringVector::iterator itGroup = groupVector.begin();
    		Ogre::StringVector::iterator itGroupEnd = groupVector.end();
    		Ogre::String shaderCoreLibsPath;
    		Ogre::String shaderCachePath;

    		for (; itGroup != itGroupEnd; ++itGroup)
    		{
    			Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(*itGroup);
    			Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
    			Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();
    			bool coreLibsFound = false;

    			// Try to find the location of the core shader lib functions and use it
    			// as shader cache path as well - this will reduce the number of generated files
    			// when running from different directories.
    			for (; it != itEnd; ++it)
    			{
    				if ((*it)->archive->getName().find("RTShaderLib") != Ogre::String::npos)
    				{
    					shaderCoreLibsPath = (*it)->archive->getName() + "/cache/";
    					shaderCachePath = shaderCoreLibsPath;
    					coreLibsFound = true;
    					break;
    				}
    			}
    			// Core libs path found in the current group.
    			if (coreLibsFound)
    				break;
    		}

    		// Core shader libs not found -> shader generating will fail.
    		if (shaderCoreLibsPath.empty())
    			return false;

    #ifdef _RTSS_WRITE_SHADERS_TO_DISK
    		// Set shader cache path.
    #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    		shaderCachePath = Ogre::macCachePath();
    #elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    		shaderCachePath = Ogre::macCachePath() + "/org.ogre3d.RTShaderCache";
    #endif
    		mShaderGenerator->setShaderCachePath(shaderCachePath);
    #endif
    #endif
    		// Create and register the material manager listener if it doesn't exist yet.
    		if (mMaterialMgrListener == NULL) {
    			mMaterialMgrListener = new ShaderGeneratorTechniqueResolverListener(mShaderGenerator);
    			Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
    		}
    	}

    	return true;
    }


};

} /* namespace Acsabo { */

#endif /* MAINSCENE_H_ */
