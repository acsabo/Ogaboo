#ifndef LEDITOR_H
#define LEDITOR_H

#include "GBaseClass.h"

#include "MainScreen.h"

using namespace Ogaboo;

class Leditor : public GBaseClass
{
    public:
        Leditor();
        virtual ~Leditor();
    protected:
    private:
        MainScreen* mainScreen;
};

#endif // LEDITOR_H
