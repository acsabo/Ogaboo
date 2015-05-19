#ifndef MAIN_H_
#define MAIN_H_
#define BOOST_BIND_NO_PLACEHOLDERS
//#include <boost/thread.hpp>
//#include <boost/date_time.hpp>
#include <OGRE/OgreSceneManager.h>

#include "MainScene.h"

using namespace std;

namespace Acsabo {


class LControl {

private:
	string file;
	MainScene* mainScene;
public:
	LControl(MainScene* mainScene, const string &file);

	virtual ~LControl();

	bool Alive();
	void run();//operator()();
};

}
#endif
