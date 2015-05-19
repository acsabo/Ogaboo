/*
 * GEntity.h
 *
 *  Created on: Jul 19, 2014
 *      Author: Adriano
 */

#ifndef GENTITY_H_
#define GENTITY_H_

#include <list>
#include <string>
#include <OGRE/Ogre.h>
#include "GAction.h"

namespace Acsabo {

class GEntity {
protected:
	std::string name;
	std::string id;
public:

	Acsabo::GAction currentTask;
	std::list<Acsabo::GAction> tasksToDo;
	GEntity();
	virtual ~GEntity();

	const std::string getId() const;
	void setId(const std::string id);
	std::string getName();
	void setName(const std::string name);
};

}

#endif /* GENTITY_H_ */
