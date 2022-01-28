#include "ActionResize.h"

ActionResize::ActionResize(ApplicationManager* pApp, CFigure* selected) :Action(pApp)
{

	Selected = selected;
}



void ActionResize::Execute()
{
	GUI* pOut = pManager->GetGUI();


	int x, y;
	if (Selected != NULL)
	{
		pOut->CreateSizeBar();

		ActionType pAct = pOut->MapInputToActionType(x, y);
		if (pAct == HALF)
		{

			Selected->Resize(.5);

		}
		else if (pAct == QUARTER)
		{
			Selected->Resize(.25);
		}
		else if (pAct == DOUBLED)
		{
			Selected->Resize(2);
		}
		else if (pAct == QUADRUPLE)
		{
			Selected->Resize(4);
		}
		else if (pAct == BACK)
		{
			pOut->CreateDrawToolBar();

			return;
		}
		pOut->ClearDrawArea();

	}
	else
		pOut->PrintMessage("Firstly, Select a fig");

	pOut->CreateDrawToolBar();

	return;
}