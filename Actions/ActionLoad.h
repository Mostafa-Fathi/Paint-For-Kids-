#pragma once
#include "Action.h"


class ActionLoad : public Action
{
public:
	//add to application manager
	ActionLoad(ApplicationManager* aApp);

	virtual void Execute();
};



