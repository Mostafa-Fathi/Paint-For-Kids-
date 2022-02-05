#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h" 
#include "..\GUI\GUI.h"

ActionAddSquare::ActionAddSquare(ApplicationManager * pApp):Action(pApp)
{


}

//Execute the action
void ActionAddSquare::Execute() 
{
	Point P1,P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	
	GfxInfo SqrGfxInfo;
	//SqrGfxInfo.isFilled = false;	//default is not filled
	SqrGfxInfo.isFilled = UI.ShapeIsFilled;	//default is not filled

	//get drawing, filling colors and pen width from the interface 
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor(); 
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();

	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Square data from the user
	//Read 1st point and store in point P1 while pointes is not in the draw area
	do {
		pGUI->PrintMessage("New Square: Click at first point (in draw area)");
		pGUI->SaveMessage("New Square: Click at first point (in draw area)");
		pGUI->GetPointClicked(P1.x, P1.y);
	} while (!pGUI->IsValueInDrawArea(P1.y));

	
	//Read 2nd point and store in point P2 while pointes is not in the draw area
	do {
	pGUI->PrintMessage("New Square: Click at second point (in draw area)");
	pGUI->SaveMessage("New Square: Click at second point (in draw area)");
	pGUI->GetPointClicked(P2.x, P2.y);
	} while (!pGUI->IsValueInDrawArea(P2.y));

	pGUI->ClearStatusBar();


	//Step 2 - prepare square data
	//User has entered two points P1&P2
	//2.1- Identify the Top left corner of the square
	Point topLeft ;
	topLeft.x = P1.x<P2.x? P1.x: P2.x;
	topLeft.y = P1.y<P2.y? P1.y: P2.y;

	//2.2- Calcuate square side legnth
	//The square side length would be the longer distance between the two points coordinates
	int SideLength = max(abs(P1.x-P2.x), abs(P1.y-P2.y));

	if (!pGUI->IsValueInDrawArea(topLeft.y + SideLength)) { pGUI->PrintMessage("this figure is too big or it will be drawn out of the draw area"); return; }

	//Step 3 - Create a Square with the parameters read from the user
	CSquare *R=new CSquare(topLeft, SideLength, SqrGfxInfo);

	//Step 4 - Add the Square to the list of figures
	pManager->AddFigure(R);
}
