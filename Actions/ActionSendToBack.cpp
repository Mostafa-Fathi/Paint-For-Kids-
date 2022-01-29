#include "ActionSendToBack.h"
#include <iostream>
ActionSendToBack::ActionSendToBack(ApplicationManager* pApp) :Action(pApp)
{
	
		Selected = pManager->GetSelectedFigure();
		Index = Selected->ID-1;
}



void ActionSendToBack::Execute()
{
	GUI* pOut =  pManager->GetGUI();
	CFigure** FigList = pManager->getFigList();
	std::cout <<"\nindex is :" << Index;
	CFigure *temp;


	
	if (Selected != NULL)
	{
		for (int i = Index; i >0; i--) {
			
			FigList[i] = FigList[i-1];
			FigList[i]->ID = i + 1;

			cout <<"\n id of fig is :" << FigList[i]->ID;
		}
		Selected->ID = 1;
		FigList[0] = Selected;
		
	}
	else
		pOut->PrintMessage("Firstly, Select a fig");

	pOut->CreateDrawToolBar();

	return;
}