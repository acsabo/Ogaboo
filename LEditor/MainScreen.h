#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

using namespace Ogaboo;

class MainScreen: public GAbstractHandler {
public:
	MainScreen();
	virtual ~MainScreen();

	void setup(const Ogaboo::GBaseClass* base);
	void load(const Ogaboo::GBaseClass* base);
	bool draw(const Ogre::FrameEvent& evt);

protected:
	Ogre::Camera* mCamera;
	CameraSet* mCameraSet;
	OgreBites::SdkCameraMan* mCameraMan;

	//Ogre::Plane mGridPlane;
	Ogre::SceneNode *mCurrentObject;
	Ogre::SceneNode* nodeCursor;
	Ogre::SceneNode* mGridPlane;

	bool addObjectAt(Ogre::Vector3 position);
	bool removeObjectAt(Ogre::Vector3 position);
	Ogre::String getKey(Ogre::Vector3 position);

private:
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	// OIS::KeyListener
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	//GUI
	void exit(MyGUI::WidgetPtr _sender);
	void saveFile(MyGUI::WidgetPtr _sender);
	void loadFile(MyGUI::WidgetPtr _sender);
	void physics(MyGUI::WidgetPtr _sender);
	void OnMouseClick_ItemListbox(MyGUI::ListBox* _sender, size_t _index);
};

#endif // MAINSCREEN_H
