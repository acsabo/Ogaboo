#include "Leditor.h"

Leditor::Leditor()
{
    //ctor
    mainScreen = new MainScreen();
	this->addHandler("mainScreen", mainScreen);
}

Leditor::~Leditor()
{
    //dtor
    delete mainScreen;
}
