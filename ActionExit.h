#pragma once
#ifndef ACTION_EXIT_H
#define ACTION_EXIT_H

#include "Actions/Action.h"

//Add Exit Action class
class ActionExit : public Action
{
public:
	ActionExit(ApplicationManager* pApp);

	//Exit the application
	virtual void Execute();

};

#endif