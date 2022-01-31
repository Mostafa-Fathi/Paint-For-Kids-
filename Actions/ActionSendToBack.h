#pragma once
#include "Action.h"
#include "../Figures/CFigure.h"
#include "../ApplicationManager.h"



class ActionSendToBack :
	public Action
{
public:
	ActionSendToBack(ApplicationManager* pApp);

	//Add ellipse to the ApplicationManager
	virtual void Execute();
};