#include "GObj.h"

#include <iostream>
using namespace std;

namespace Acsabo {

GObj::GObj(const std::string fileName) {
	this->fileName = fileName;
	this->life = 100;
	this->aceleration = 0;
	this->name = fileName;
	this->action = ActionType::BORN;
	this->mNode = NULL;
	this->mEntity = NULL;

	// Set default values for variables
	mWalkSpeed = 0.0f;
	mDistance = 0.0f;
	mDirection = Ogre::Vector3::ZERO;
	mAnimationState = NULL;

cout << " created " << fileName << endl;
}

GObj::~GObj() {

}

bool GObj::nextLocation(void){
    if (mWalkList.empty()) return false;
    mDestination = mWalkList.front();  // this gets the front of the deque
    mWalkList.pop_front();             // this removes the front of the deque
    mDirection = mDestination - mNode->getPosition();
    mDistance = mDirection.normalise();
    return true;
}

int GObj::getLife() {
	return life;
}

void GObj::TakeAction(ActionType action) {
	this->action = action;
}


void GObj::addStep(float x, float y, float z)
{
	this->mWalkList.push_back(Ogre::Vector3(x, y, z));
}

void GObj::Update(float tms) {
	this->mNode->rotate(Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(1,0,0)) , Ogre::Node::TransformSpace::TS_WORLD);
/*
	if (mDirection == Ogre::Vector3::ZERO) {
		if (nextLocation()) {
			// Set walking animation
			mAnimationState = mEntity->getAnimationState("Walk");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);
		} //if
	} else {
		Ogre::Real move = mWalkSpeed * tms;
		mDistance -= move;
		if (mDistance <= 0.0f) {
			mNode->setPosition(mDestination);
			mDirection = Ogre::Vector3::ZERO;
			// Set animation based on if the robot has another point to walk to.
			if (!nextLocation()) {
				// Set Idle animation
				mAnimationState = mEntity->getAnimationState("Idle");
				mAnimationState->setLoop(true);
				mAnimationState->setEnabled(true);
			} else {
				// Rotation Code will go here later
				Ogre::Vector3 src = mNode->getOrientation()
						* Ogre::Vector3::UNIT_X;
				if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
					mNode->yaw(Ogre::Degree(180));
				} else {
					Ogre::Quaternion quat = src.getRotationTo(mDirection);
					mNode->rotate(quat);
				} // else
			} //else
		} else {
			mNode->translate(mDirection * move);
		} // else
	} // if
	mAnimationState->addTime(tms);
*/

//	/**
//	 * idéia para substituir switch case: criar um map de funções e retornar a função correspondente ativa.
//	 */
//	switch (action) {
//	case ActionType::BORN: {
//		TakeAction(ActionType::WALK);
//		this->aceleration = 1;
//		break;
//	}
//
//	case ActionType::WALK: {
//
//		break;
//	}
//
//	case ActionType::STOP: {
//
//		break;
//	}
//
//	}
}

void GObj::setLife(const int life) {
	this->life = life;
}

const string GObj::getFileName() {
	return fileName;
}

void GObj::setFileName(const std::string fileName) {
	this->fileName = fileName;
}

void GObj::setAnimationState(const std::string state)
{

	this->mAnimationState = this->mEntity->getAnimationState(state);
	this->mAnimationState->setLoop(true);
	this->mAnimationState->setEnabled(true);
	this->mWalkSpeed = 35.0f;

cout << "setAnimationState" << endl;
}

}
