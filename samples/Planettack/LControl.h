#ifndef MAIN_H_
#define MAIN_H_

//#include <functional>
//#include <boost/thread/once.hpp>
//
//using namespace std::placeholders;

//#define BOOST_BIND_NO_PLACEHOLDERS
//#include <boost/thread.hpp>
//#include <boost/date_time.hpp>
// for back-compatibility ...
//#include "boost/function.hpp"
//#include "boost/bind.hpp"
//#include "boost/lambda/lambda.hpp"
//using boost::placeholders::_1;

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
