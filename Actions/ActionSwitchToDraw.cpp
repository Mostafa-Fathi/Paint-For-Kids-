#include "ActionSwitchToDraw.h"
#include "../ApplicationManager.h"

ActionSwitchToDraw::ActionSwitchToDraw(ApplicationManager* pApp):Action(pApp)
{
}

void ActionSwitchToDraw::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	pGUI->CreateDrawToolBar();

	pGUI->PrintMessage("Switched to draw mode");
}


