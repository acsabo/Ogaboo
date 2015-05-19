#include "LControl.h"
#include "GObj.h"

#include <luacppinterface.h>
#include "Subject.h"   // Our Subject class#include "EventType.h" // Our EventType enumeration#include <iostream>#include <OGRE/Ogre.h>

using namespace std;
using namespace Acsabo;
using namespace Ogre;

static bool alive = true;

namespace Acsabo {

LControl::LControl(MainScene* mainScene, const string &file) {
	this->mainScene = mainScene;
	this->file = file;
	alive = true;
}

bool LControl::Alive() {
	return alive;
}

LControl::~LControl() {

}

void foo(int i) {
	std::cout << "foo ( " << i << " )\n";
}

void bar() {
	std::cout << "bar()\n";
}


LuaUserdata<GEntity> GEntityConstructor(Lua lua) {
	auto obj = new GEntity();
	auto userData = lua.CreateUserdata<GEntity>(obj);

	userData.Bind("getName", &GEntity::getName);
	userData.Bind("setName", &GEntity::setName);

	return userData;
}

LuaUserdata<GObj> GObjConstructor(Lua lua, std::string str) {
	auto obj = new GObj(str);
	auto userData = lua.CreateUserdata<GObj>(obj);

	userData.Bind("getName", &GObj::getName);
	userData.Bind("setName", &GObj::setName);
	userData.Bind("getLife", &GObj::getLife);
	userData.Bind("addStep", &GObj::addStep);
	userData.Bind("setAnimationState", &GObj::setAnimationState);

	return userData;
}

string getfile(const string& filename) {
    ifstream in(filename.c_str(), ios_base::binary);
    in.exceptions(ios_base::badbit | ios_base::failbit | ios_base::eofbit);
    return string(istreambuf_iterator<char>(in), istreambuf_iterator<char>());
}

void LControl::run() { //operator()() {

//	Subject<EventType> s;
//	s.registerObserver(EventType::GREEN, bar);
//
//	s.registerObserver(EventType::ORANGE, std::bind(foo, 42));
//	s.registerObserver(EventType::RED, std::bind(foo, 12345));
//
//	s.notify(EventType::GREEN);
//	s.notify(EventType::RED);
//	s.notify(EventType::ORANGE);
//
	alive = true;
	Lua lua;

	lua.LoadStandardLibraries();

	auto newEntity = lua.CreateFunction<LuaUserdata<GEntity>(void)>(
			std::bind(&GEntityConstructor, lua));
	auto entityTable = lua.CreateTable();
	entityTable.Set("new", newEntity);
	lua.GetGlobalEnvironment().Set("GEntity", entityTable);


	auto newObj = lua.CreateFunction<LuaUserdata<GObj>(std::string)>(
			std::bind(&GObjConstructor, lua, std::placeholders::_1));
	auto footable = lua.CreateTable();
	footable.Set("new", newObj);
	lua.GetGlobalEnvironment().Set("GObj", footable);

	// Create the userdata instance
	auto mainScene = lua.CreateUserdata<Acsabo::MainScene>(this->mainScene);
	lua.GetGlobalEnvironment().Set("MainScene", mainScene);
	mainScene.Bind("addObject", &MainScene::addObject);

	auto lControl = lua.CreateUserdata<Acsabo::LControl>(this);
	lua.GetGlobalEnvironment().Set("LControl", lControl);
	lControl.Bind("Alive", &LControl::Alive);

	lua.RunScript(getfile(this->file));

	alive = false;

}

}
