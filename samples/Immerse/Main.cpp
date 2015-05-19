/*
 * Main.cpp
 *
 *  Created on: 19/05/2015
 *      Author: a.sabo
 */

#include "Main.h"
#include "LineReader.h"

#include <iostream>

Main::Main() {
	// TODO Auto-generated constructor stub

}

Main::~Main() {
	// TODO Auto-generated destructor stub
}

int main()
{
	LineReader* reader = new LineReader();
	reader->readLines("file.dxf");

	printf ("done");
}
