#pragma once
#include "Action.h"
#include "../Figures/CFigure.h"
#include "../ApplicationManager.h"



class ActionSendToBack :
	public Action
{
	CFigure* Selected;
	int Index;
public:
	ActionSendToBack(ApplicationManager* pApp, CFigure*,int index);

	//Add ellipse to the ApplicationManager
	virtual void Execute();
};