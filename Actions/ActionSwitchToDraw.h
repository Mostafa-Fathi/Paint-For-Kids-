#pragma once
#include "Action.h"

class ActionSwitchToDraw : public Action {

public:
	ActionSwitchToDraw(ApplicationManager* pApp);

	virtual void Execute();
};
