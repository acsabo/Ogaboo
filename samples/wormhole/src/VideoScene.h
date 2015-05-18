#ifndef VIDEOSCENE_H
#define VIDEOSCENE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

using namespace Ogaboo;

class VideoScene : public GAbstractHandler
{
    public:
        VideoScene(GBaseClass *base);
        ~VideoScene();

        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);
    private:
        TheoraVideoClip* clip;
};

#endif // VIDEOSCENE_H
