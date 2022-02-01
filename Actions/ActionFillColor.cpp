#include "ActionFillColor.h"

ActionFillColor::ActionFillColor(ApplicationManager* pApp) :Action(pApp)
{
	Selected = pManager->GetSelectedFigure();

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
		if (Selected != NULL) {
			UI.ShapeIsFilled = true;
			Selected->ChngFillClr(UI.oldFillColor);
		}
	}
	else if (pAct == REDFILL)
	{
		pGUI->PrintMessage("red clicked"); 
		UI.ShapeIsFilled = true;
		UI.FillColor = RED;
		if (Selected != NULL) 
			Selected->ChngFillClr(RED);

	}
	else if (pAct == BLUEFILL)
	{
		pGUI->PrintMessage("blue clicked"); 
		UI.ShapeIsFilled = true;
		UI.FillColor = BLUE;
		if (Selected != NULL)
			Selected->ChngFillClr(BLUE);

	}
	else if (pAct == GREENFILL)
	{
		pGUI->PrintMessage("green clicked");
		UI.ShapeIsFilled = true;
		UI.FillColor = GREEN;
		if (Selected != NULL)
			Selected->ChngFillClr(GREEN);


	} 
	pOut->ClearDrawArea(); 

	pOut->CreateDrawToolBar();

	return;
}