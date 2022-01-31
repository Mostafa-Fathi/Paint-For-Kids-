#include "ActionFillColor.h"

ActionFillColor::ActionFillColor(ApplicationManager* pApp) :Action(pApp)
{
}
  
void ActionFillColor::Execute()
{
	GUI* pOut = pManager->GetGUI();
	pOut->CreateFillColorBar();
	 
	int x, y;
 
	GUI* pGUI = pManager->GetGUI();
	ActionType pAct = pOut->MapInputToActionType(x, y);
	if (pAct == EMPTYFILL)
	{ 
		pGUI->PrintMessage("empty clicked"); 
		UI.ShapeIsFilled = false;
	}
	else if (pAct == REDFILL)
	{
		pGUI->PrintMessage("red clicked"); 
		UI.ShapeIsFilled = true;
		UI.FillColor = RED;

	}
	else if (pAct == BLUEFILL)
	{
		pGUI->PrintMessage("blue clicked"); 
		UI.ShapeIsFilled = true;
		UI.FillColor = BLUE;

	}
	else if (pAct == GREENFILL)
	{
		pGUI->PrintMessage("green clicked");
		UI.ShapeIsFilled = true;
		UI.FillColor = GREEN;


	} 
	pOut->ClearDrawArea(); 

	pOut->CreateDrawToolBar();

	return;
}