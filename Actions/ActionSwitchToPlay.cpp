#include "ActionSwitchToPlay.h"

ActionSwitchToPlay::ActionSwitchToPlay(ApplicationManager* pApp) :Action(pApp)
{
	
}

void ActionSwitchToPlay::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	
	pGUI->CreatePlayToolBar();

	pGUI->PrintMessage("Switched to Play mode");

	pManager->Game = new Game();

	CFigure* fig = pManager->GetSelectedFigure();
	if (fig != NULL) {
		fig->SetSelected(false);
		fig->ChngDrawClr(fig->GetPreviousDrawColor());
	}
}
