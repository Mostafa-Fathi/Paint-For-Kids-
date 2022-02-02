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
		
		if (Selected != NULL) {
			Selected->ChngFillClr(EMPTYFILL);
		}
		else UI.ShapeIsFilled = false;
	}
	else if (pAct == REDFILL)
	{
		pGUI->PrintMessage("red clicked"); 

		if (Selected != NULL) 
			Selected->ChngFillClr(RED);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = RED; 
		}
	}

	else if (pAct == BLUEFILL)
	{
		pGUI->PrintMessage("blue clicked"); 

		if (Selected != NULL)
			Selected->ChngFillClr(BLUE);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = BLUE;
		}

	}
	else if (pAct == GREENFILL)
	{
		pGUI->PrintMessage("green clicked");

		if (Selected != NULL)
			Selected->ChngFillClr(GREEN);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = GREEN;
		}

	} 
	else if (pAct == WHITEFILL)
	{
		pGUI->PrintMessage("WHITE clicked");

		if (Selected != NULL)
			Selected->ChngFillClr(WHITE);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = WHITE;
		}
	}
	else if (pAct == BLACKFILL)
	{
		pGUI->PrintMessage("black clicked");

		if (Selected != NULL)
			Selected->ChngFillClr(BLACK);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = BLACK;
		}
	}
	else if (pAct == BROWNFILL)
	{
		pGUI->PrintMessage("brown clicked");

		if (Selected != NULL)
			Selected->ChngFillClr(BROWN);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = BROWN;
		}
	}
	else if (pAct ==  ORANGEFILL)
	{
		pGUI->PrintMessage("orange clicked");

		if (Selected != NULL)
			Selected->ChngFillClr(ORANGE);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = ORANGE;
		}
	}
	else if (pAct == YELLOWFILL)
	{
		pGUI->PrintMessage("YELLOW clicked");

		if (Selected != NULL)
			Selected->ChngFillClr(YELLOW);
		else {
			UI.ShapeIsFilled = true;
			UI.FillColor = YELLOW;
		}
	}
	 
	pOut->ClearDrawArea(); 

	pOut->CreateDrawToolBar();

	return;
}