/*
 * GAction.h
 *
 *  Created on: Jul 20, 2014
 *      Author: Adriano
 */

#ifndef GACTION_H_
#define GACTION_H_

#include <string>

namespace Acsabo {

class GAction {
public:
	GAction();
	virtual ~GAction();
	float progress;
	void* target;
	int action;
};

} /* namespace acsabo */

#endif /* GACTION_H_ */
