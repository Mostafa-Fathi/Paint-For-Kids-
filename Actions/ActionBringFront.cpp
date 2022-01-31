#include "ActionBringFront.h"
#include "ActionSendToBack.h"
#include <iostream>
ActionBringFront::ActionBringFront(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionBringFront::Execute()
{
	pManager->BringSelectedFigFront();
	
	return;
}