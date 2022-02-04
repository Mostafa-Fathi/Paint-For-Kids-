#pragma once

#include "Action.h"

class ActionPlayModeSelect : public Action
{
public:
	ActionPlayModeSelect(ApplicationManager* pApp);

	virtual void Execute();

};