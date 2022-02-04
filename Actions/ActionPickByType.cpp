#include "..\ApplicationManager.h"
#include "ActionPickByType.h"


ActionPickByType::ActionPickByType(ApplicationManager* pApp) :Action(pApp) {

}

void ActionPickByType::Execute() {
	
	pManager->ShowAllFig();
	pManager->Game->Valid = 0;
	pManager->Game->InValid = 0;
	pManager->Game->Mode = ByType;
	pManager->UpdateInterface();
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Pick By Type Mode Activated");
}