
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <tr1/unordered_map>
#include <iostream>
#include <tinyxml.h>

#include "MainScreen.h"

#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h> // for static planes
#include <Shapes/OgreBulletCollisionsConvexHullShape.h>
#include <Utils/OgreBulletCollisionsMeshToShapeConverter.h>

using namespace std::tr1;
using namespace std;
namespace fs = ::boost::filesystem;

const int MAX_RANGE = 50;
const int SNAP_SIZE = 2;

bool drawing = false;
bool rotatingMouseAround = false;

Ogre::String currentType;
unordered_map<std::string, Ogre::Entity*> objects;
Ogre::Entity* entGround;

int numberOfObjects = 0;


MainScreen::MainScreen() : GAbstractHandler("mainScreen")
{
	mCameraSet = new Camera_Set();
    mCurrentObject = NULL;
    mGridPlane = NULL;
    nodeCursor = NULL;
}

MainScreen::~MainScreen()
{
    //dtor
}

float snap (float f)
{
    int r = (int)f % SNAP_SIZE;
    int diff = 0;
    if (r > 0.5f) diff = SNAP_SIZE;
    return ((int)(f / SNAP_SIZE)) * SNAP_SIZE + diff;
}

// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories
void get_all(const fs::path& root, const string& ext, vector<fs::path>& ret)
{
  if (!fs::exists(root)) return;

  if (fs::is_directory(root))
  {
    fs::recursive_directory_iterator it(root);
    fs::recursive_directory_iterator endit;
    while(it != endit)
    {
      if (fs::is_regular_file(*it) and it->path().extension() == ext)
      {
        ret.push_back(it->path().filename());
      }
      ++it;
    }
  }
}

//------------ GUI events

void MainScreen::loadFile (MyGUI::WidgetPtr _sender)
{

	TiXmlDocument *xmlDoc =  new TiXmlDocument("level.xml");

	bool loaded = xmlDoc->LoadFile(TIXML_DEFAULT_ENCODING);

	TiXmlElement *obj = (TiXmlElement *) xmlDoc->FirstChildElement();
	obj = obj->FirstChildElement("object");

	cout << "loading..." << loaded << " - " <<  obj << endl;
	while (obj)
	{
		const char* currentType = obj->Attribute("name");

		cout << "currentType: " << currentType << endl;

		TiXmlElement *posElt = obj->FirstChildElement("position");
		Ogre::Vector3 position = Ogre::Vector3(atof(posElt->Attribute("x")), atof(posElt->Attribute("y")), atof(posElt->Attribute("z")));

		TiXmlElement *oriElt = obj->FirstChildElement("orientation");
		float roll = atof(oriElt->Attribute("roll"));
		float pitch = atof(oriElt->Attribute("pitch"));
		float yaw = atof(oriElt->Attribute("yaw"));
		Ogre::Quaternion quat = Ogre::Quaternion();


		TiXmlElement *sclElt = obj->FirstChildElement("scale");
		Ogre::Vector3 scale = Ogre::Vector3(atof(sclElt->Attribute("x")), atof(sclElt->Attribute("y")), atof(sclElt->Attribute("z")));

		Ogre::Entity* entity = mSceneMgr->createEntity(currentType + Ogre::StringConverter::toString(numberOfObjects++), currentType);
		entity->setCastShadows(true);
		Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		node->setPosition(position);
		node->setOrientation(1, roll, pitch, yaw);
		node->setScale(scale);
		node->attachObject(entity);

		obj = obj->NextSiblingElement("object");
	}

	cout << "end." << endl;
}

void MainScreen::saveFile (MyGUI::WidgetPtr _sender)
{
	TiXmlDocument *xmlDoc =  new TiXmlDocument("level.xml");
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
 	xmlDoc->LinkEndChild( decl );

	TiXmlElement *root = new TiXmlElement( "scene" );
	xmlDoc->LinkEndChild( root );


	for ( auto local_it = objects.begin(); local_it!= objects.end(); ++local_it  )
	{
		std::cout << " " << local_it->first << ":" << local_it->second << endl;

		Ogre::Entity * obj = local_it->second;

		TiXmlElement * element = new TiXmlElement( "object" );

		element->SetAttribute("name", obj->getMesh()->getName().c_str());

		TiXmlElement * posElt = new TiXmlElement("position");
        Ogre::Vector3 pos = obj->getParentNode()->getPosition();
        posElt->SetAttribute("x", pos.x);
        posElt->SetAttribute("y", pos.y);
        posElt->SetAttribute("z", pos.z);
        element->LinkEndChild(posElt);

        TiXmlElement * oriElt = new TiXmlElement("orientation");
        Ogre::Quaternion quat = obj->getParentNode()->getOrientation();
        oriElt->SetAttribute("roll", quat.getRoll().valueDegrees());
        oriElt->SetAttribute("pitch", quat.getPitch().valueDegrees());
        oriElt->SetAttribute("yaw", quat.getYaw().valueDegrees());
        element->LinkEndChild(oriElt);

        TiXmlElement * sclElt = new TiXmlElement("scale");
        Ogre::Vector3 scale = obj->getParentNode()->getScale();
        sclElt->SetAttribute("x", scale.x);
        sclElt->SetAttribute("y", scale.y);
        sclElt->SetAttribute("z", scale.z);
        element->LinkEndChild(sclElt);

        root->LinkEndChild(element);
	}
	xmlDoc->SaveFile();

}

void MainScreen::physics (MyGUI::WidgetPtr _sender)
{
	for ( auto local_it = objects.begin(); local_it!= objects.end(); ++local_it  )
	{
		Ogre::Entity * obj = local_it->second;

		OgreBulletCollisions::StaticMeshToShapeConverter * converter = new OgreBulletCollisions::StaticMeshToShapeConverter(obj);

		OgreBulletCollisions::CollisionShape *shape = (OgreBulletCollisions::CollisionShape*) converter->createBox();//createConvex();

        // and the Bullet rigid body
        OgreBulletDynamics::RigidBody* defaultBody = new OgreBulletDynamics::RigidBody(obj->getName(), mWorld);

        defaultBody->setShape( obj->getParentSceneNode(),
        						shape,
        						0.5f, 0.5f, 0.5f, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);

        //defaultBody->getBulletRigidBody()->setFlags(defaultBody->getBulletRigidBody()->getFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

 cout << "added " << obj->getName() << endl;
	}

	 cout << "physics DONE" << endl;
}

void MainScreen::OnMouseClick_ItemListbox(MyGUI::ListBox* _sender, size_t _index)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::OnMouseClick_ItemListbox  --- ***" + _sender->getItem(_index), Ogre::LML_NORMAL);

     currentType = _sender->getItem(_index);

}

void MainScreen::exit(MyGUI::WidgetPtr _sender)
{
	Ogre::LogManager::getSingleton().logMessage("*** --- MainMenu::exit  --- ***", Ogre::LML_NORMAL);
	this->kill();
}

//------------------------------

Ogre::String MainScreen::getKey(Ogre::Vector3 position)
{
	long x = snap(position.x);
	long y = snap(position.y);
	long z = snap(position.z);

    //register the type of cursor
	Ogre::String key =  Ogre::StringConverter::toString(x) + ":" +
			Ogre::StringConverter::toString(y) + ":" +
			Ogre::StringConverter::toString(z);

	return key;
}

bool MainScreen::addObjectAt(Ogre::Vector3 position)
{
	Ogre::String key = getKey(position);

	//prevents more than one object at the same position in space
	if (objects[key]) return false;

	Ogre::Entity* obj = mSceneMgr->createEntity(currentType + Ogre::StringConverter::toString(numberOfObjects++), currentType);
	obj->setCastShadows(true);
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	long x = snap(position.x);
	long y = snap(position.y);
	long z = snap(position.z);

	node->setPosition (x, y, z);
	//node->setScale(5, 5, 5);
	node->attachObject(obj);

    objects[key] = obj;
    return true;
}

bool MainScreen::removeObjectAt(Ogre::Vector3 position)
{
	Ogre::String key = getKey(position);

	if (objects[key])
	{
		Ogre::Entity* obj = objects[key];
		obj->getParentNode()->getParent()->removeChild(obj->getParentNode());
		objects.erase(key);
	}
	return true;
}

bool MainScreen::mouseMoved(const OIS::MouseEvent &arg)
{
	if (rotatingMouseAround)
	{
		mCameraMan->injectMouseMove(arg);
	} else
    if (drawing) return true;

    Ogre::Real x = arg.state.X.abs / float(arg.state.width);
    Ogre::Real y = arg.state.Y.abs / float(arg.state.height);

    // Setup the ray scene query
    Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(x, y);
    mRayScnQuery->setRay(mouseRay);

    // Execute query
    Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
    // Get results, create a node/entity on the position
    for(Ogre::RaySceneQueryResult::iterator itr = result.begin(); itr != result.end(); itr++)
    {
        if(itr->movable)
        {
            if (mCurrentObject)
            {
                Ogre::Vector3 position = mouseRay.getPoint(itr->distance);
                nodeCursor->setPosition (snap(position.x), snap(position.y), snap(position.z));
                break;
            }
        }

    }

    return true;
}

bool MainScreen::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	mCameraMan->injectMouseDown(arg, id);
	//deselect current object
	if (mCurrentObject)
	{
		mCurrentObject->showBoundingBox(false);
		mCurrentObject = NULL;
	}

   if(id == OIS::MB_Left)
	{
      drawing = true;

      Ogre::Real x = arg.state.X.abs / float(arg.state.width);
      Ogre::Real y = arg.state.Y.abs / float(arg.state.height);

      // Setup the ray scene query
      Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(x, y);
      mRayScnQuery->setRay(mouseRay);

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
		    	//try to find the grid only
		    	if (mCurrentObject == mGridPlane)// nodeCursor)
		    	{
					//nodeCursor->setPosition (mouseRay.getPoint(itr->distance));
					if (!currentType.empty())
					{
						Ogre::Vector3 position = mouseRay.getPoint(itr->distance);

						addObjectAt(position);

					}
					break;
		    	}
            }
         }
      }
      nodeCursor->setVisible(true);
    }
    else
    if(id == OIS::MB_Middle)
    {
    	rotatingMouseAround = true;
    } else
    if(id == OIS::MB_Right)
    {
        Ogre::Real x = arg.state.X.abs / float(arg.state.width);
        Ogre::Real y = arg.state.Y.abs / float(arg.state.height);

        // Setup the ray scene query
        Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(x, y);
        mRayScnQuery->setRay(mouseRay);
        mRayScnQuery->setSortByDistance(true);

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

  		    	nodeCursor->setVisible(false);
  		    	break;
              }
           }
        }

    }

    return true;
}

bool MainScreen::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	mCameraMan->injectMouseUp(arg, id);

    if(id == OIS::MB_Left)
    {
        drawing = false;
    }
    else
    if (id == OIS::MB_Middle)
    {
    	rotatingMouseAround = false;
    }

    return true;
}

bool MainScreen::keyPressed( const OIS::KeyEvent &arg )
{

	//exit
	if (arg.key == OIS::KC_ESCAPE)
	{
		return false;
	}

	mCameraMan->injectKeyDown(arg);

    if (arg.key == OIS::KC_HOME)
    {
        mGridPlane->setPosition(mGridPlane->getPosition() + Ogre::Vector3(0, 0, 0));
    }
    if (arg.key == OIS::KC_PERIOD)
    {
        mGridPlane->setPosition(mGridPlane->getPosition() + Ogre::Vector3(0,SNAP_SIZE,0));
    }
    if (arg.key == OIS::KC_COMMA)
    {
        mGridPlane->setPosition(mGridPlane->getPosition() - Ogre::Vector3(0,SNAP_SIZE,0));
    }

    if (arg.key == OIS::KC_G)
    {
    	mCurrentObject->setPosition(mCurrentObject->getPosition() + Ogre::Vector3(SNAP_SIZE/2, 0, 0));
    }
    if (arg.key == OIS::KC_F)
    {
    	mCurrentObject->setPosition(mCurrentObject->getPosition() + Ogre::Vector3(-SNAP_SIZE/2, 0, 0));
    }

    if (arg.key == OIS::KC_R)
    {
    	mCurrentObject->yaw(Ogre::Degree(90));
    }

    if (arg.key == OIS::KC_DELETE)
    {
    	if (mCurrentObject != mGridPlane)
    	{
    		removeObjectAt(mCurrentObject->getPosition());
    	}
    }

    if (arg.key == OIS::KC_N)
    {
        OgreOggSound::OgreOggSoundManager* mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();

        mSoundManager->getSound("Sound1")->play();

    }

    return true;
}

bool MainScreen::keyReleased( const OIS::KeyEvent &arg )
{
	mCameraMan->injectKeyUp(arg);

    return true;
}

//void subscribeEvent(const CEGUI::String& widget, const CEGUI::String& event, const CEGUI::Event::Subscriber& method)
//{
//	CEGUI::Window* root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
//    if (root->isChild(widget))
//    {
//    	CEGUI::Window* window = root->getChild(widget);
//        window->subscribeEvent(event, method);
//    }
//}

void MainScreen::setup(const Ogaboo::GBaseClass* base)
{
	Ogre::LogManager::getSingleton().logMessage("*** ---  MainScreen::setup(void) --- ***", Ogre::LML_NORMAL);
    // Get the SceneManager, in this case a generic one
    mSceneMgr = base->mRoot->createSceneManager(Ogre::ST_GENERIC);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

	//Fix for 1.9
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
    //mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);


    mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Ogre::Vector3(70, 70, 70));
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));
    mCamera->setNearClipDistance(0.1);
    mCamera->setFarClipDistance(50000);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);
    mCameraSet->mCamera = mCamera;
    this->addCameraSet(mCameraSet);
}

void MainScreen::load(const Ogaboo::GBaseClass* base)
{
	// load layout
	MyGUI::LayoutManager::getInstance().loadLayout("ledit_main.layout");

	//Register GUI events
	MyGUI::MenuItem* mi_exit = MyGUI::Gui::getInstance().findWidget<MyGUI::MenuItem>("m_exit");
	mi_exit->eventMouseButtonClick += MyGUI::newDelegate(this, &MainScreen::exit);

	MyGUI::MenuItem* mi_save = MyGUI::Gui::getInstance().findWidget<MyGUI::MenuItem>("m_save");
	mi_save->eventMouseButtonClick += MyGUI::newDelegate(this, &MainScreen::saveFile);

	MyGUI::MenuItem* mi_load = MyGUI::Gui::getInstance().findWidget<MyGUI::MenuItem>("m_load");
	mi_load->eventMouseButtonClick += MyGUI::newDelegate(this, &MainScreen::loadFile);

	MyGUI::MenuItem* mi_physics = MyGUI::Gui::getInstance().findWidget<MyGUI::MenuItem>("m_physics");
	mi_physics->eventMouseButtonClick += MyGUI::newDelegate(this, &MainScreen::physics);

	Ogre::LogManager::getSingleton().logMessage("*** ---  MainScreen::createScene --- ***", Ogre::LML_NORMAL);

	// I create a light. The scenemanager will contain it.
	// I will attach this light to a scenenode, so that I can move it easily.
	// (This will add 1 transformation matrix, but I prefer to control motion homogeneously for all elements).
	Ogre::SceneNode* lLightSceneNode = NULL;
	{
		Ogre::Light* lLight =mSceneMgr->createLight();

		// I can set some attributes of the light.
		// The basic light type can be :
		//		pointlight (like a candle?)
		//		spotlight (kind of 'conic' light)
		//		directional light (like the sun in an outdoor scene).
		// Directional light is like parallel rays coming from 1 direction.
		lLight->setType(Ogre::Light::LT_DIRECTIONAL);

		// Here I choose the color of the light.
		// The diffuse color is the main color of the light.
		// The specular color is its color when reflected on an imperfect surface.
		// For example, when my bald head skin reflect the sun, it makes a bright round of specular color.
		//
		// The final color of an object also depends on its material.
		lLight->setDiffuseColour(1.0f, 1.0f, 1.0f);
		lLight->setSpecularColour(1.0f, 1.0f, 1.0f);// color of 'reflected' light

		lLightSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		lLightSceneNode->attachObject(lLight);
		lLightSceneNode->setPosition(0, 500, 0);
	}

    //LOAD ALL THE MESHES
    {
    	MyGUI::ListBox* mi_listBox = MyGUI::Gui::getInstance().findWidget<MyGUI::ListBox>("ListBox");
    	mi_listBox->eventListSelectAccept += MyGUI::newDelegate(this, &MainScreen::OnMouseClick_ItemListbox);

        fs::path my_path( "./resources" );

        typedef vector<fs::path> vec;         // store paths,
        vec v;                                // so we can sort them later

        get_all(my_path, ".mesh", v);

        for (vec::const_iterator it (v.begin()); it != v.end(); ++it)
        {
            fs::path path = (fs::path)*it;

            mi_listBox->addItem(path.string());
        }
    }


	Ogre::LogManager::getSingleton().logMessage("*** ---  MainScreen::createScene 2 --- ***", Ogre::LML_NORMAL);

    //create the GRID
    Ogre::Plane plane = Ogre::Plane (Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane, SNAP_SIZE, SNAP_SIZE, SNAP_SIZE, SNAP_SIZE, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);

    entGround = mSceneMgr->createEntity("GroundEntity", "Base.mesh");
    entGround->setCastShadows(true);
    nodeCursor = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeCursor->attachObject(entGround);

    //------
    Ogre::LogManager::getSingleton().logMessage("*** ---  MainScreen::createScene 3 --- ***", Ogre::LML_NORMAL);

    Ogre::ManualObject* myManualObject = mSceneMgr->createManualObject("manual1");
    mGridPlane = mSceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node");

    // NOTE: The second parameter to the create method is the resource group the material will be added to.
    // If the group you name does not exist (in your resources.cfg file) the library will assert() and your program will crash
    Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material","General");
    myManualObjectMaterial->setReceiveShadows(false);
    myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1);
    myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1);
    myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST);

    Ogre::LogManager::getSingleton().logMessage("*** ---  MainScreen::createScene 4 --- ***", Ogre::LML_NORMAL);

    //X plane grid
    for (int x = -MAX_RANGE; x <= MAX_RANGE; x+= SNAP_SIZE)
    {
        myManualObject->position(x, 0, MAX_RANGE);
        myManualObject->position(x, 0, -MAX_RANGE);
    }

    //Y plane grid
    for (int z = -MAX_RANGE; z <= MAX_RANGE; z+= SNAP_SIZE)
    {
        myManualObject->position(MAX_RANGE, 0, z);
        myManualObject->position(-MAX_RANGE, 0, z);
    }

    myManualObject->end();

    mGridPlane->attachObject(myManualObject);

    //------------physics
    // Start Bullet
    Ogre::AxisAlignedBox box = Ogre::AxisAlignedBox(Ogre::Vector3(-10000.0f, -10000.0f, -10000.0f),	Ogre::Vector3(10000.0f, 10000.0f, 10000.0f));

    mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, box, Ogre::Vector3(0.0f, -98.1f * 2.0f, 0.0f));
    mWorld->setShowDebugShapes(true);

    OgreBulletCollisions::CollisionShape *Shape;
    Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)

    //OgreBulletCollisions::StaticMeshToShapeConverter * converter = new OgreBulletCollisions::StaticMeshToShapeConverter(entGround);
    //OgreBulletCollisions::CollisionShape *Shape = (OgreBulletCollisions::CollisionShape*) converter->createConcave();//createConvex();

    OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody(
                   "GroundEntity",
                   mWorld);
    defaultPlaneBody->setStaticShape(Shape, 0.8, 10.8); // (shape, restitution, friction)

    //------------Create Sounds
    //Load sounds fot the menu
    OgreOggSound::OgreOggSoundManager* mSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
    // Create a streamed sound, no looping, no prebuffering
    mSoundManager->createSound("Sound1", "test.ogg", true, false, false);
}

bool MainScreen::draw(const Ogre::FrameEvent& evt)
{
    mCameraMan->frameRenderingQueued(evt);

    //update physics
    mWorld->stepSimulation(evt.timeSinceLastFrame);
    return true;
}


