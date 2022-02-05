#pragma once

#include "Action.h"

//Add Exit Action class
class ActionPickByType : public Action
{
public:
	ActionPickByType(ApplicationManager* pApp);

	virtual void Execute();

};