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

    void addObject(const std::string name, GObj* obj);
    bool keyPressed( const OIS::KeyEvent &arg );
};

} /* namespace Acsabo { */

#endif /* MAINSCENE_H_ */
