#include "ActionSwitchToPlay.h"

ActionSwitchToPlay::ActionSwitchToPlay(ApplicationManager* pApp) :Action(pApp)
{
	
}

void ActionSwitchToPlay::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	
	pGUI->CreatePlayToolBar();

	pGUI->PrintMessage("Switched to Play mode");

}
