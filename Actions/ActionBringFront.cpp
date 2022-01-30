#include "ActionBringFront.h"
#include "ActionSendToBack.h"
#include <iostream>
ActionBringFront::ActionBringFront(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionBringFront::Execute()
{
	GUI* pOut = pManager->GetGUI();
	CFigure** FigList = pManager->getFigList();
	CFigure* Selected = pManager->GetSelectedFigure();
	if (Selected != NULL)
	{
		int Index = Selected->ID - 1;

		for (int i = Index; i < pManager->getFigCount()-1; i++) {
			//cout << "\n fig count is =" << pManager->getFigCount()-1;
			FigList[i] = FigList[i + 1];
			FigList[i]->ID = i+1;

			//cout << "\n id of fig is :" << FigList[i]->ID;
		}
		Selected->ID = pManager->getFigCount();
		FigList[pManager->getFigCount()-1] = Selected;
		

	}
	else
		pOut->PrintMessage("Firstly, Select a fig");
	return;
}