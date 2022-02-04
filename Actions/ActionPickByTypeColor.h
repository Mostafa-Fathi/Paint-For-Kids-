#pragma once
#include "Action.h"

//Add Exit Action class
class ActionPickByTypeColor : public Action
{
public:
	ActionPickByTypeColor(ApplicationManager* pApp);

	virtual void Execute();

}; 