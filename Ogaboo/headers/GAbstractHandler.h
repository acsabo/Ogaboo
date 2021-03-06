/*
 * Ogaboo (Open Game Bootstrap) 1.0
 * https://sourceforge.net/projects/ogaboo/
 *
 * Copyright (c) 2014 Adriano de Castro Sabo
 * acsabo@hotmail.com
 *
 * Licensed under http://opensource.org/licenses/MIT
 */

#ifndef GABSTRACTHANDLER_H
#define GABSTRACTHANDLER_H
#include <vector>

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/InputContext.h>
#include <OGRE/SdkCameraMan.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>

//Shader
#include <OGRE/RTShaderSystem/OgreRTShaderSystem.h>
#include <OGRE/RTShaderSystem/OgreShaderGenerator.h>

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
	#include <OIS/OISMultiTouch.h>
#else
	#include <OIS/OISMouse.h>
	#include <OGRE/InputContext.h>
#endif

//Ogre Bullet
#include <OgreBullet/Collisions/OgreBulletCollisions.h>
#include <OgreBullet/Dynamics/OgreBulletDynamics.h>
#include <OgreBullet/Dynamics/OgreBulletDynamicsWorld.h>
#include <OgreBullet/Dynamics/OgreBulletDynamicsRigidBody.h>

namespace Ogaboo {

//forward reference due to dependency
class GBaseClass;

typedef struct Camera_Set
{
	Ogre::Camera* mCamera;
//	OgreBites::SdkCameraMan* mCameraMan;
} CameraSet;

/** This class demonstrates basic usage of the RTShader system.
It sub class the material manager listener class and when a target scheme callback
is invoked with the shader generator scheme it tries to create an equivalent shader
based technique based on the default technique of the given material.
*/
class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
{
public:

	ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator)
	{
		mShaderGenerator = pShaderGenerator;
	}

	/** This is the hook point where shader based technique will be created.
	It will be called whenever the material manager won't find appropriate technique
	that satisfy the target scheme name. If the scheme name is out target RT Shader System
	scheme name we will try to create shader generated technique for it.
	*/
	virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
		const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex,
		const Ogre::Renderable* rend)
	{
		Ogre::Technique* generatedTech = NULL;

		// Case this is the default shader generator scheme.
		if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
		{
			bool techniqueCreated;

			// Create shader generated technique for this material.
			techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
				originalMaterial->getName(),
				Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
				schemeName);

			// Case technique registration succeeded.
			if (techniqueCreated)
			{
				// Force creating the shaders for the generated technique.
				mShaderGenerator->validateMaterial(schemeName, originalMaterial->getName());

				// Grab the generated technique.
				Ogre::Material::TechniqueIterator itTech = originalMaterial->getTechniqueIterator();

				while (itTech.hasMoreElements())
				{
					Ogre::Technique* curTech = itTech.getNext();

					if (curTech->getSchemeName() == schemeName)
					{
						generatedTech = curTech;
						break;
					}
				}
			}
		}

		return generatedTech;
	}

	virtual bool afterIlluminationPassesCreated(Ogre::Technique* tech)
	{
		if(tech->getSchemeName() == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
		{
			Ogre::Material* mat = tech->getParent();
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
			mShaderGenerator->validateMaterialIlluminationPasses(tech->getSchemeName(), mat->getName(), mat->getGroup());
#else
			mShaderGenerator->validateMaterial(tech->getSchemeName(), mat->getName(), mat->getGroup());
#endif
			return true;
		}
		return false;
	}

	virtual bool beforeIlluminationPassesCleared(Ogre::Technique* tech)
	{
		if(tech->getSchemeName() == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
		{
			Ogre::Material* mat = tech->getParent();
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
			mShaderGenerator->invalidateMaterialIlluminationPasses(tech->getSchemeName(), mat->getName(), mat->getGroup());
#else
			mShaderGenerator->invalidateMaterial(tech->getSchemeName(), mat->getName(), mat->getGroup());
#endif
			return true;
		}
		return false;
	}

protected:
	Ogre::RTShader::ShaderGenerator*	mShaderGenerator;			// The shader generator instance.
};


    class GAbstractHandler  : public OIS::KeyListener,
							  #if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
							  public OIS::MultiTouchListener
							  #else
                              public OIS::MouseListener
							  #endif
    {
        public:
            GAbstractHandler(std::string name);
            virtual ~GAbstractHandler();
            std::string mName;

            virtual void setup(const Ogaboo::GBaseClass* base) = 0; // Override me!
            virtual void load(const Ogaboo::GBaseClass* base) = 0; // Override me!
            virtual bool draw(const Ogre::FrameEvent& evt) = 0; // Override me!

            // OIS::KeyListener
            bool keyPressed( const OIS::KeyEvent &arg );
            bool keyReleased( const OIS::KeyEvent &arg );
			
			#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
            // OIS::MultiTouchListener
			bool touchMoved( const OIS::MultiTouchEvent &arg ){return true;};
			bool touchPressed( const OIS::MultiTouchEvent &arg ){return true;};
			bool touchReleased( const OIS::MultiTouchEvent &arg ){return true;};
			bool touchCancelled( const OIS::MultiTouchEvent &arg ){return true;};
			#else
            // OIS::MouseListener
			bool mouseMoved(const OIS::MouseEvent &arg);
			bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
			bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	        #endif

            CameraSet* getCameraSet (int index = 0);
            void kill (void);
            bool isAlive (void);
            Ogre::SceneManager* mSceneMgr;

        protected:

            //Fix for 1.9
        	Ogre::OverlaySystem *mOverlaySystem;
        	//pointer to our ray scene query
            Ogre::RaySceneQuery* mRayScnQuery;
            //ogre bullet World
            OgreBulletDynamics::DynamicsWorld* mWorld;

        	std::vector <CameraSet*> mCameraSet;
            void addCameraSet (CameraSet* cameraSet);

        private:
            bool alive;
    };
};
#endif // GABSTRACTHANDLER_H
