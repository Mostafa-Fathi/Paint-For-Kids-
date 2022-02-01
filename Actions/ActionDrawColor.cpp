#include "ActionDrawColor.h"

ActionDrawColor::ActionDrawColor(ApplicationManager* pApp) :Action(pApp)
{
	Selected = pManager->GetSelectedFigure();
}

void ActionDrawColor::Execute()
{
	GUI* pOut = pManager->GetGUI();
	pOut->CreateDrawColorBar();

	int x, y;

	GUI* pGUI = pManager->GetGUI();
	ActionType pAct = pOut->MapInputToActionType(x, y);
	if (pAct == DRAW_RED)
	{
		pGUI->PrintMessage("red  ");
		if (Selected != NULL) {
			Selected->ChngDrawClr(RED);
		}
		UI.DrawColor = RED;
	}
	else if (pAct == DRAW_ORANGE)
	{
		pGUI->PrintMessage("orange  ");
		UI.DrawColor = ORANGE;
		if (Selected != NULL)
			Selected->ChngDrawClr(ORANGE);
	}
	else if (pAct == DRAW_BLUE)
	{
		pGUI->PrintMessage("blue  ");
		UI.DrawColor = BLUE;
		if (Selected != NULL)
			Selected->ChngDrawClr(BLUE);
	}
	else if (pAct == DRAW_GREEN)
	{
		pGUI->PrintMessage("green  ");
		UI.DrawColor = GREEN; 
		if (Selected != NULL)
			Selected->ChngDrawClr(GREEN);
	}
	else
		pGUI->PrintMessage("error");

	pOut->ClearDrawArea();

	pOut->CreateDrawToolBar();

	return;
}