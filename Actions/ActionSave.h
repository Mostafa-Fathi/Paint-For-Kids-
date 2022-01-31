#pragma once

#include "Action.h"
class ActionSave : public Action
{
private:
	string FileName;
	int FiguresCount;
public:
	ActionSave(ApplicationManager* pApp,int Figures_Count);
	virtual void Execute();
};

