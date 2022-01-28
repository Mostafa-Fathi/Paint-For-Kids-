#include "ActionBringFront.h"
#include "ActionSendToBack.h"
#include <iostream>
ActionBringFront::ActionBringFront(ApplicationManager* pApp, CFigure* selected, int index) :Action(pApp)
{
	Index = index;
	Selected = selected;
}



void ActionBringFront::Execute()
{
	GUI* pOut = pManager->GetGUI();
	CFigure** FigList = pManager->getFigList();
	std::cout << "\nindex is :" << Index;
	CFigure* temp;
	if (Selected != NULL)
	{
		for (int i = Index; i < pManager->getFigCount()-1; i++) {
			cout << "\n fig count is =" << pManager->getFigCount()-1;
			FigList[i] = FigList[i + 1];

			cout << "\n id of fig is :" << FigList[i]->ID;
		}
		FigList[pManager->getFigCount()-1] = Selected;
		pOut->ClearDrawArea();

	}
	else
		pOut->PrintMessage("Firstly, Select a fig");

	pOut->CreateDrawToolBar();

	return;
}