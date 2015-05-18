#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

class MainScene : public GAbstractHandler
{
    public:
        MainScene(GBaseClass *base);
        virtual ~MainScene();

        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);

    protected:
    private:
};

#endif // MAINSCENE_H
