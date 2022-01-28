#include "ActionSendToBack.h"
#include <iostream>
ActionSendToBack::ActionSendToBack(ApplicationManager* pApp, CFigure* selected ,int index) :Action(pApp)
{
	Index = index;
	Selected = selected;
}



void ActionSendToBack::Execute()
{
	GUI* pOut =  pManager->GetGUI();
	// test git hup 
	CFigure** FigList = pManager->getFigList();
	std::cout <<"\nindex is :" << Index;
	CFigure *temp;


	
	if (Selected != NULL)
	{
		for (int i = Index; i >0; i--) {
			
			FigList[i] = FigList[i-1];

			cout <<"\n id of fig is :" << FigList[i]->ID;
		}
		FigList[0] = Selected;
		pOut->ClearDrawArea();
		
	}
	else
		pOut->PrintMessage("Firstly, Select a fig");

	pOut->CreateDrawToolBar();

	return;
}