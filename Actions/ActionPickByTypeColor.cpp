#include "..\ApplicationManager.h"
#include "ActionPickByTypeColor.h"


ActionPickByTypeColor::ActionPickByTypeColor(ApplicationManager* pApp) :Action(pApp) {

}

void ActionPickByTypeColor::Execute() {

	pManager->ShowAllFig();
	pManager->Game->Valid = 0;
	pManager->Game->InValid = 0;
	pManager->Game->Mode = ByTypeAndColor;
	pManager->UpdateInterface();
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Pick By Type And Color Mode Activated");
}