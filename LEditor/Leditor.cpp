#include "Leditor.h"

Leditor::Leditor()
{
    //ctor
    mainScreen = new MainScreen(this);
}

Leditor::~Leditor()
{
    //dtor
    delete mainScreen;
}
