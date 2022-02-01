#include "ActionResize.h"

ActionResize::ActionResize(ApplicationManager* pApp) :Action(pApp)
{

	Selected = pManager->GetSelectedFigure();
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
			Selected->Resize(.5,pOut);
		}
		else if (pAct == QUARTER)
		{
			Selected->Resize(.25,pOut);
		}
		else if (pAct == DOUBLED)
		{
			
			if (!Selected->Resize(2, pOut)) {
				Selected->Resize(.5, pOut);
				pOut->PrintMessage("This Fig cannot be more bigger ");
			}
			
		}
		else if (pAct == QUADRUPLE)
		{
			if (!Selected->Resize(4, pOut)) {
				Selected->Resize(.25, pOut);
				pOut->PrintMessage("This Fig cannot be more bigger ");
			}
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