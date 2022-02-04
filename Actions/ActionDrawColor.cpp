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
		else UI.DrawColor = RED;
	}
	else if (pAct == DRAW_ORANGE)
	{
		pGUI->PrintMessage("orange  ");
		if (Selected != NULL)
			Selected->ChngDrawClr(ORANGE);
		else UI.DrawColor = ORANGE;
	}
	else if (pAct == DRAW_BLUE)
	{
		pGUI->PrintMessage("blue  ");
		if (Selected != NULL)
			Selected->ChngDrawClr(BLUE);
		else UI.DrawColor = BLUE;

	}
	else if (pAct == DRAW_GREEN)
	{
		pGUI->PrintMessage("green  ");
		if (Selected != NULL)
			Selected->ChngDrawClr(GREEN);
		else UI.DrawColor = GREEN;

	}
	pOut->CreateDrawToolBar();

	return;
}