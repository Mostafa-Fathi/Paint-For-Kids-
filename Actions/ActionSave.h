#pragma once

#include "Action.h"
class ActionSave : public Action
{
private:
	string FileName;
public:
	ActionSave(ApplicationManager* pApp);
	virtual void Execute();
};

