/*
 * MainMenu.h
 *
 *  Created on: 11 de set de 2015
 *      Author: acsab
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <GBaseClass.h>
#include <GAbstractHandler.h>

using namespace Ogaboo;

class MainMenu : public GAbstractHandler
{
public:
	MainMenu();
	virtual ~MainMenu();

    void setup(const Ogaboo::GBaseClass* base);
    void load(const Ogaboo::GBaseClass* base);
    bool draw(const Ogre::FrameEvent& evt);

private:
    CameraSet* mCameraSet;
    OgreBites::SdkCameraMan* mCameraMan;

    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);

    //MYGUI events
    void exit(MyGUI::WidgetPtr _sender);
    void notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old);
};

#endif /* MAINMENU_H_ */
