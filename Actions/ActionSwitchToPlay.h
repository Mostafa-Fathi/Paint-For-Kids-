#pragma once
#include "../ApplicationManager.h"
#include "./Action.h"

class ActionSwitchToPlay : public Action {


	public:
		ActionSwitchToPlay(ApplicationManager* pApp);

		virtual void Execute();
};