#include "MainMenuScene.h"
#include <iostream>

//para integrar com bullet
#include <OGRE/Terrain/OgreTerrain.h>
#include <OgreBullet/Collisions/Shapes/OgreBulletCollisionsTerrainShape.h>
#include <OgreBullet/Collisions/Shapes/OgreBulletCollisionsSphereShape.h>

#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "string.h" // for the memcpy

//Bullet API
/*
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
*/

using namespace std;

//btRigidBody* fallRigidBody;

MainMenuScene::MainMenuScene() :GAbstractHandler("mainMenuScene")
{
	cameraSet1 = new Camera_Set();
    //ctor
}

MainMenuScene::~MainMenuScene()
{
    //dtor
}

void MainMenuScene::setup(const Ogaboo::GBaseClass &base)
{
//    // Get the SceneManager, in this case a generic one
//    mSceneMgr = this->game->mRoot->createSceneManager(Ogre::ST_GENERIC);
//    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
//
//    mCamera = mSceneMgr->createCamera("PlayerCam");
//    mCamera->setPosition(Ogre::Vector3(1683, 150, 2116));
//    mCamera->lookAt(Ogre::Vector3(1963, 50, 1660));
//    mCamera->setNearClipDistance(0.1);
//    mCamera->setFarClipDistance(50000);
//
//    mCameraMan = new OgreBites::SdkCameraMan(mCamera);
//
//    // Create one viewport, entire window
//    mViewport = this->game->mWindow->addViewport(mCamera,2);
//    mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
//
//    // Alter the camera aspect ratio to match the viewport
//    mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
//
//    cameraSet1->mCamera = mCamera;
//    cameraSet1->mCameraMan = mCameraMan;
//    //cameraSet1->mViewport = mViewport;
//
//    this->addCameraSet(cameraSet1);
//    // Start Bullet
//    Ogre::AxisAlignedBox box = Ogre::AxisAlignedBox(Ogre::Vector3(-10000.0f, -10000.0f, -10000.0f),	Ogre::Vector3(10000.0f, 10000.0f, 10000.0f));
//
//    //se comentar compila
//    mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, box, Ogre::Vector3(0.0f, -98.1f * 2.0f, 0.0f));
//    //mWorld->setShowDebugShapes(true);
//
////    void MainMenuScene::createScene(void)
//
//	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
//	lightdir.normalise();
//
//	Ogre::Light* light = mSceneMgr->createLight("tstLight");
//	light->setType(Ogre::Light::LT_DIRECTIONAL);
//	light->setDirection(lightdir);
//	light->setDiffuseColour(Ogre::ColourValue::White);
//	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
//
//	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
//
//	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
//
//	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
//	mTerrainGroup->setFilenameConvention(Ogre::String("map"), Ogre::String("dat"));
//	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
//
//	configureTerrainDefaults(light);
//
//	for (long x = 0; x <= 0; ++x)
//		for (long y = 0; y <= 0; ++y)
//			defineTerrain(x, y);
//
//	// sync load since we want everything in place when we start
//	mTerrainGroup->loadAllTerrains(true);
//
//	if (mTerrainsImported)
//	{
//		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
//		while(ti.hasMoreElements())
//		{
//			Ogre::Terrain* t = ti.getNext()->instance;
//			initBlendMaps(t);
//
//			//integra com bullet
//			addToWorld(t);
//		}
//	}
//
//	mTerrainGroup->freeTemporaryResources();
//	Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
//	//   mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
//	game->mWindow->getViewport(0)->setBackgroundColour(fadeColour);
//
//	Ogre::Plane plane;
//	plane.d = 100;
//	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
//
//	//mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 500);
//	mSceneMgr->setSkyPlane(true, plane, "Examples/CloudySky", 500, 20, true, 0.5, 150, 150);
//
//	//but we also want to set up our raySceneQuery after everything has been initialized
//	mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());
//
//	//ADR!
//	gContactAddedCallback = CustomMaterialCombinerCallback;
//
//	//Este funciona
//	gContactProcessedCallback = MyContactProcessedCallback;
}

//
//extern ContactProcessedCallback gContactProcessedCallback;

//ADR!
static bool MyContactProcessedCallback(btManifoldPoint& cp, void* body0,void* body1)
{
 //   std::cout << " collide 1!" << endl;
    return false;
}

static bool CustomMaterialCombinerCallback(btManifoldPoint& cp,	const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1)
{
    std::cout << "----------------------------- collide 2! " << endl;
    return false;
}

void MainMenuScene::addToWorld(Ogre::Terrain* t)
{
    int terrainPageSize = t->getSize(); // Number of vertices along x/z axe

    // >>> We need to mirror the ogre-height-data along the z axis first!
    // This is related to how Ogre and Bullet differ in heighmap storing
    float *pTerrainHeightData = t->getHeightData();
    float pTerrainHeightDataConvert[terrainPageSize * terrainPageSize];
    for(int i = 0; i < terrainPageSize; ++i)
    {
        memcpy(pTerrainHeightDataConvert + terrainPageSize * i,
               pTerrainHeightData + terrainPageSize * (terrainPageSize - i - 1),
               sizeof(float)*(terrainPageSize));
    }
    // <<< End of conversion

    btHeightfieldTerrainShape* pHeightShape = new btHeightfieldTerrainShape(terrainPageSize,
                                            terrainPageSize,
                                            pTerrainHeightDataConvert,
                                            1, /* Terrains getHeightData() is already scaled perfectly */
                                            t->getMinHeight(),
                                            t->getMaxHeight(),
                                            1, /* upVector is Y positive in ogre-, bullet- and our world */
                                            PHY_FLOAT,
                                            true);

    // Scale the mesh along x/z
    float unitsBetweenVertices = t->getWorldSize() / (terrainPageSize - 1);
    btVector3 scaling(unitsBetweenVertices, 1, unitsBetweenVertices);
    pHeightShape->setLocalScaling(scaling);

    // Ogre uses DiamonSubdivision for Terrain-mesh, so bullet should use it too
    pHeightShape->setUseDiamondSubdivision(true);

    // Now we create a btRigidBody
    btRigidBody *pBody = new btRigidBody(0.0 /* mass 0.0 means static */,
                                         new btDefaultMotionState(),
                                         pHeightShape);

    //
    Ogre::Vector3 terrainPosition = t->getPosition();
    pBody->getWorldTransform().setOrigin(btVector3(terrainPosition.x,
                                                   terrainPosition.y
                                                   + (t->getMaxHeight() - t->getMinHeight()) / 2,
    // Bullet's position differs from Ogre's. Ogre's y is at the bottom, bullet needs the middle if the height to be positioned right
                                                   terrainPosition.z));

    pBody->getWorldTransform().setRotation(btQuaternion(Ogre::Quaternion::IDENTITY.x,
                                                        Ogre::Quaternion::IDENTITY.y,
                                                        Ogre::Quaternion::IDENTITY.z,
                                                        Ogre::Quaternion::IDENTITY.w));

//            game->dynamicsWorld->addRigidBody(pBody);
    mWorld->getBulletDynamicsWorld()->addRigidBody(pBody);

    cout << ">> adicionado!" << endl;

    // Advanced Body configuration ->
    // You can play with these or just leave the defaults:
    pBody->setFriction(1.0);
    pBody->setRestitution(0.0);
    pBody->setHitFraction(0.0);
    pBody->setDamping(0.2, 0.2);
}

bool MainMenuScene::draw(const Ogre::FrameEvent& evt)
{
    mCameraMan->frameRenderingQueued(evt);

    if (mTerrainGroup->isDerivedDataUpdateInProgress())
    {

    }
    else
    {
        if (mTerrainsImported)
        {
            mTerrainGroup->saveAllTerrains(true);
            mTerrainsImported = false;
            cout << ">>> mTerrainGroup->isDerivedDataUpdateInProgress() mTerrainsImported" << endl;
        }
    }

    mWorld->stepSimulation(evt.timeSinceLastFrame);

    return true;
}

//-------------------------------------------------------------------------------------
void MainMenuScene::destroyScene(void)
{
    OGRE_DELETE mTerrainGroup;
    OGRE_DELETE mTerrainGlobals;
}
//-------------------------------------------------------------------------------------
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	//img.load("terreno.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX)
        img.flipAroundY();
    if (flipY)
        img.flipAroundX();
}
//-------------------------------------------------------------------------------------
void MainMenuScene::defineTerrain(long x, long y)
{
    Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }
}
//-------------------------------------------------------------------------------------
void MainMenuScene::initBlendMaps(Ogre::Terrain* terrain)
{
    Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;

            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend0++ = val;

            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}
//-------------------------------------------------------------------------------------
void MainMenuScene::configureTerrainDefaults(Ogre::Light* light)
{
    // Configure global
    mTerrainGlobals->setMaxPixelError(8);
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000);

    // Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

    // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
    // textures
    defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 100;
/*
 https://code.google.com/p/vdrift-ogre/issues/detail?id=155
 To fix black overlay, we need png not dds for all terrain textures, anyone could fix it by resaving in Gimp (it's tedious to do it for each textures).

 */
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.png");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.png");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.png");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.png");
    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.png");
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.png");
}
//-------------------------------------------------------------------------------------

bool MainMenuScene::mouseMoved( const OIS::MouseEvent &arg )
{
    GAbstractHandler::mouseMoved(arg);
    return true;
}

bool MainMenuScene::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    GAbstractHandler::mousePressed(arg, id);
    if(id == OIS::MB_Left)
	{
      Ogre::Real x = arg.state.X.abs / float(arg.state.width);
      Ogre::Real y = arg.state.Y.abs / float(arg.state.height);

      // Setup the ray scene query
      Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(x, y);
      mRayScnQuery->setRay(mouseRay);
      //mRayScnQuery->setQueryTypeMask(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);

      // Execute query
      Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
      // Get results, create a node/entity on the position
      for(Ogre::RaySceneQueryResult::iterator itr = result.begin(); itr != result.end(); itr++)
      {
         if(itr->movable)
         {
		    mCurrentObject = itr->movable->getParentSceneNode();
		    if (mCurrentObject)
            {
                mCurrentObject->showBoundingBox(true);
                std::cout << ">> selected = " << mCurrentObject->getName() << endl;
                //break;
            }
         } // if
      } // for
	}
    return true;
}

bool MainMenuScene::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    GAbstractHandler::mouseReleased(arg, id);
    return true;
}

bool MainMenuScene::keyReleased( const OIS::KeyEvent &arg )
{

}

int num=1;
bool MainMenuScene::keyPressed( const OIS::KeyEvent &arg )
{
    if (arg.key == OIS::KC_B)
    {
        //sphere to test bullet
        Ogre::Entity* sphereEntity = mSceneMgr->createEntity("sphere"+Ogre::StringConverter::toString(num++), "sphere.mesh");
        Ogre::SceneNode* sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

        sphereNode->attachObject(sphereEntity);
        sphereEntity->setMaterialName("Examples/Targets");
        sphereEntity->setCastShadows(true);
        sphereNode->setScale(1, 1, 1);

        OgreBulletCollisions::SphereCollisionShape *sceneBallShape = new OgreBulletCollisions::SphereCollisionShape(100); //acge o raio
        // and the Bullet rigid body
        OgreBulletDynamics::RigidBody* defaultBody = new OgreBulletDynamics::RigidBody(
                       "bola"+Ogre::StringConverter::toString(num++),mWorld);

        defaultBody->setShape( sphereNode,
                                   sceneBallShape,
                                   0.1f,         // dynamic body restitution
                                   0.1f,         // dynamic body friction
                                   1.0f,          // dynamic bodymass
                                   mCameraMan->getCamera()->getPosition(),// starting position of the box
                                   Ogre::Quaternion(0,0,0,1));// orientation of the box


        //ADR!
        defaultBody->getBulletRigidBody()->setFlags(defaultBody->getBulletRigidBody()->getFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    }
    if (arg.key == OIS::KC_V)
    {
    /** colidir com a camera */

        Ogre::SceneNode* mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CameraNode");

        mSceneNode->attachObject(mCamera);
        mSceneNode->setOrientation(mCamera->getOrientation());
        //mSceneNode->setDirection(mCamera->getDirection());

        OgreBulletCollisions::SphereCollisionShape *shape = new OgreBulletCollisions::SphereCollisionShape(100); //acge o raio

        // and the Bullet rigid body
        OgreBulletDynamics::RigidBody* defaultBody = new OgreBulletDynamics::RigidBody(
                       "camera",mWorld);


        defaultBody->setShape(mSceneNode,
                                   shape,
                                   0.6f,         // dynamic body restitution
                                   0.6f,         // dynamic body friction
                                   1.0f,          // dynamic bodymass
                                   mCameraMan->getCamera()->getPosition(),// starting position of the box
                                   Ogre::Quaternion(0,0,0,1));// orientation of the box

        mCamera->setPosition(Ogre::Vector3(0,0,0)); //make the cam centered
        mCamera->setOrientation(mSceneNode->getOrientation());

    /** --------------- */
    }

    return true;
}

