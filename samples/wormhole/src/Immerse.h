#ifndef IMMERSE_H
#define IMMERSE_H

#include <GBaseClass.h>
#include <GAbstractHandler.h>

class Immerse : public GAbstractHandler
{
    public:
		Immerse(GBaseClass *base);
        virtual ~Immerse();

        void setup(void);
        void createScene(void);
        bool draw(const Ogre::FrameEvent& evt);

    protected:
    private:
};

#endif // IMMERSE_H
