/*
 * Splash.h
 *
 *  Created on: 14 de set de 2015
 *      Author: acsab
 */

#ifndef SPLASH_H_
#define SPLASH_H_

#include <GBaseClass.h>
#include <GAbstractHandler.h>

namespace Ogaboo {

class Splash : public GAbstractHandler
{
public:
	Splash();
	virtual ~Splash();

    void setup(const Ogaboo::GBaseClass* base);
    void load(const Ogaboo::GBaseClass* base);
    bool draw(const Ogre::FrameEvent& evt);

protected:
    const Ogaboo::GBaseClass* game;
private:
    CameraSet* mCameraSet;
    bool keyPressed( const OIS::KeyEvent &arg );

    //MYGUI events
    void exit(MyGUI::WidgetPtr _sender);
    void notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old);

};

} /* namespace Ogaboo */

#endif /* SPLASH_H_ */
