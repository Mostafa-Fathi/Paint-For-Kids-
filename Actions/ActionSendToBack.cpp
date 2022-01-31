#include "ActionSendToBack.h"
#include <iostream>
ActionSendToBack::ActionSendToBack(ApplicationManager* pApp) :Action(pApp)
{	
}



void ActionSendToBack::Execute()
{
	pManager->SendSelectedFigBack();
	
	return;
}