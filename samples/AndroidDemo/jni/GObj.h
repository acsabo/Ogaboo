#ifndef GOBJ_H_
#define GOBJ_H_

#include <string>
#include <OGRE/Ogre.h>

#include "GEntity.h"

namespace Acsabo {

enum class ActionType { BORN, WALK, STAND, FIGHT, DEFEND, STOP };

class GObj : public Acsabo::GEntity {

private:

	std::string fileName;
	int life;
	ActionType action;
	float aceleration;

public:
	Ogre::AnimationState *mAnimationState; // The current animation state of the object
	Ogre::SceneNode* mNode;
	Ogre::Entity* mEntity;
	Ogre::Real mDistance;                  // The distance the object has left to travel
	Ogre::Vector3 mDirection;              // The direction the object is moving
	Ogre::Vector3 mDestination;            // The destination the object is moving towards


    std::deque<Ogre::Vector3> mWalkList;   // The list of points we are walking to
    Ogre::Real mWalkSpeed;                 // The speed at which the object is moving

	GObj(const std::string fileName);
	virtual ~GObj();

	void addStep(float x, float y, float z);

	bool nextLocation(void);
	int getLife();
	void Update(float tms);
	void setLife(const int life);
	void TakeAction(ActionType action);

	const std::string getFileName();
	void setFileName(const std::string fileName);

	void setAnimationState(const std::string state);

	//overrides
	std::string getName()
	{
		return GEntity::getName();
	}
	void setName(const std::string name)
	{
		GEntity::setName(name);
	}
};

}

#endif
