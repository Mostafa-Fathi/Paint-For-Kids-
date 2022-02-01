#include "ActionAddPolygon.h"
#include "..\Figures\CPolygon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddPolygon::ActionAddPolygon(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddPolygon::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = UI.ShapeIsFilled;	 
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Square data from the user

	//Read 1st point and store in point P1 while pointes is not in the draw area
	do {
		pGUI->PrintMessage("New Square: Click at first point (in draw area)");
		pGUI->GetPointClicked(P1.x, P1.y);
	} while (!pGUI->IsClickInDrawArea(P1.y));


	//Read 2nd point and store in point P2 while pointes is not in the draw area
	do {
		pGUI->PrintMessage("New Square: Click at second point (in draw area)");
		pGUI->GetPointClicked(P2.x, P2.y);
	} while (!pGUI->IsClickInDrawArea(P2.y));

	pGUI->ClearStatusBar();

	//Step 2 - prepare square data
	//User has entered two points P1&P2
	//2.1- Identify the Top left corner of the square
	Point topLeft;
	topLeft.x = P1.x < P2.x ? P1.x : P2.x;
	topLeft.y = P1.y < P2.y ? P1.y : P2.y;

	//2.2- Calcuate square side legnth
	//The square side length would be the longer distance between the two points coordinates
	int SideLength = max(abs(P1.x - P2.x), abs(P1.y - P2.y));

	if (!pGUI->IsClickInDrawArea(topLeft.y + SideLength))return;

	//Step 3 - Create a Square with the parameters read from the user
	CPolygon* R = new CPolygon(topLeft, SideLength, SqrGfxInfo);

	//Step 4 - Add the Square to the list of figures
	pManager->AddFigure(R);
}
