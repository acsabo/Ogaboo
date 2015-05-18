/*
 * GEntity.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: Adriano
 */

#include "GEntity.h"

namespace Acsabo {

GEntity::GEntity() {

}

GEntity::~GEntity() {
	// TODO Auto-generated destructor stub
}

const std::string GEntity::getId() const {
	return id;
}

void GEntity::setId(const std::string id) {
	this->id = id;
}

std::string GEntity::getName() {
	return name;
}

void GEntity::setName(const std::string name) {
	this->name = name;
}
} /* namespace acsabo */
