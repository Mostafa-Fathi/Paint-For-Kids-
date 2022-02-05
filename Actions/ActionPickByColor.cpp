#include "..\ApplicationManager.h"
#include "ActionPickByColor.h"


ActionPickByColor::ActionPickByColor(ApplicationManager* pApp) :Action(pApp) {

}

void ActionPickByColor::Execute() {

	pManager->ShowAllFig();
	pManager->Game->Valid = 0;
	pManager->Game->InValid = 0;
	pManager->Game->MaxScore = 0;
	pManager->Game->Mode = ByColor;
	pManager->UpdateInterface();
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Pick By Color Mode Activated");
}