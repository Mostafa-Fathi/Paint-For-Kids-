#include "..\ApplicationManager.h"
#include "ActionPlayModeSelect.h"


ActionPlayModeSelect::ActionPlayModeSelect(ApplicationManager* pApp) :Action(pApp) {

}

void ActionPlayModeSelect::Execute() {
	GUI* pGUI = pManager->GetGUI();
	if (pManager->Game->Mode != None) {
		CFigure* fig = pManager->GetFigure(pManager->X, pManager->Y);
		if (fig != NULL) {
			if (pManager->Game->InValid == 0 && pManager->Game->Valid == 0) {
				pManager->Game->SelectedType = fig->GetType();
				pManager->Game->SelectedColor = fig->GetFillColor();
				pManager->Game->SelectedFillState = fig->IsFilled();
			}
			switch (pManager->Game->Mode) {
			case ByType:
				if (fig->GetType() == pManager->Game->SelectedType)
				{
					pManager->Game->Valid++;
					fig->HideMe();
				}
				else pManager->Game->InValid++;
				break;

			case ByColor:
			{
				if (pManager->Game->SelectedFillState) {
					if (fig->GetFillColor() == pManager->Game->SelectedColor && fig->IsFilled())
					{
						pManager->Game->Valid++;
						fig->HideMe();
					}
					else pManager->Game->InValid++;
				}
				else {
					if (!fig->IsFilled())
					{
						pManager->Game->Valid++;
						fig->HideMe();
					}
					else pManager->Game->InValid++;
				}
				break;
			}

			case ByTypeAndColor:
				if (fig->GetType() == pManager->Game->SelectedType) {
					if (pManager->Game->SelectedFillState) {
						if (fig->GetFillColor() == pManager->Game->SelectedColor && fig->IsFilled())
						{
							pManager->Game->Valid++;
							fig->HideMe();
						}
						else pManager->Game->InValid++;
					}
					else {
						if (!fig->IsFilled())
						{
							pManager->Game->Valid++;
							fig->HideMe();
						}
						else pManager->Game->InValid++;
					}
				}
				break;
			}

			pManager->UpdateInterface();
			pGUI->PrintMessage("valid = " + to_string(pManager->Game->Valid) + ", invalid = " + to_string(pManager->Game->InValid));
		}
	}
	else {
		pGUI->PrintMessage("Please Select Mode First To Start The Game");
	}
}