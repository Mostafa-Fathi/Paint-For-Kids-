#pragma once
#include "Action.h"

//Add Exit Action class
class ActionPickByColor : public Action
{
public:
	ActionPickByColor(ApplicationManager* pApp);

	virtual void Execute();

};