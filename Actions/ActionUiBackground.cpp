#include "ActionUiBackground.h"

ActionUiBackground::ActionUiBackground(ApplicationManager* pApp) :Action(pApp)
{ 
}

void ActionUiBackground::Execute()
{
	GUI* pOut = pManager->GetGUI();
	pOut->CreatebackgroundBar();

	int x, y;

	GUI* pGUI = pManager->GetGUI();
	ActionType pAct = pOut->MapInputToActionType(x, y);
	  
	if (pAct == BACKG_BURLYWOOD)
		UI.BkGrndColor = BURLYWOOD;

	else if (pAct == BACKG_blanchedalmond)
		UI.BkGrndColor = BLANCHEDALMOND; 

	else if (pAct == BACKG_LIGHTGOLDENRODYELLOW)
		UI.BkGrndColor = LIGHTGOLDENRODYELLOW;

	pOut->ClearDrawArea();

	pOut->CreateDrawToolBar();

	return;
}