#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

class MainScene : public GAbstractHandler
{
    public:
        MainScene();
        virtual ~MainScene();

        void setup(const Ogaboo::GBaseClass &base);
        bool draw(const Ogre::FrameEvent& evt);

    protected:
    private:
        CameraSet* cameraSet1;
};

#endif // MAINSCENE_H
