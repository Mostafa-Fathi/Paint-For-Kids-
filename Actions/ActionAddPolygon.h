#ifndef ACTION_ADD_POLYGON_H
#define ACTION_ADD_POLYGON_H

#include "Action.h"

//Add Square Action class
class ActionAddPolygon : public Action
{
public:
	ActionAddPolygon(ApplicationManager* pApp);

	//Add Square to the ApplicationManager
	virtual void Execute();

};

#endif