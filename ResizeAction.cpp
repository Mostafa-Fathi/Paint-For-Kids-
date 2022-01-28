#include "ResizeAction.h"

ResizeAction::ResizeAction(ApplicationManager* pApp, CFigure* selected) :Action(pApp)
{

	Selected = selected;
}

void ResizeAction::ReadActionParameters()
{
}

void ResizeAction::Execute()
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
			pOut->ClearDrawArea();

		}
		else if (pAct == QUARTER)
		{
			Selected->Resize(.25);
			pOut->ClearDrawArea();
		}
		else if (pAct == DOUBLED)
		{
			Selected->Resize(2);
			pOut->ClearDrawArea();
		}
		else if (pAct == QUADRUPLE)
		{
			Selected->Resize(4);
			pOut->ClearDrawArea();
		}
		else if (pAct == BACK)
		{
			pOut->CreateDrawToolBar();

			return;
		}
	}
	else
	pOut->PrintMessage("Firstly, Select a fig");

	pOut->CreateDrawToolBar();

	return;
}