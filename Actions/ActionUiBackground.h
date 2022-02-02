#pragma once
 
#include "..\Actions/Action.h"
#include "..\ApplicationManager.h"


class ActionUiBackground :
	public Action
{ 
public:
	ActionUiBackground(ApplicationManager* pApp);

	virtual void Execute();
};

