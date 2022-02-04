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
				pManager->CalcMaxScore();
				

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
			if (pManager->Game->Valid == pManager->Game->MaxScore && pManager->Game->MaxScore) {
				pManager->UpdateInterface();
				pGUI->PrintMessage("valid = " + to_string(pManager->Game->Valid) + ", invalid = " + to_string(pManager->Game->InValid));
				string message = "\tYou reached to Max Score ="+ to_string(pManager->Game->MaxScore)+" \n\twith clicks  =" + to_string(pManager->Game->InValid + pManager->Game->Valid);
				int n = message.length();

				// declaring character array
				char* char_array= new char [n + 1];

				// copying the contents of the
				// string to char array
				strcpy(char_array, message.c_str());
				MessageBox(NULL, char_array, "Congratulations", MB_OK);
				pManager->ShowAllFig();
				pManager->Game->Valid = 0;
				pManager->Game->InValid = 0;
				pManager->Game->MaxScore = 0;
			}

			pManager->UpdateInterface();
			pGUI->PrintMessage("valid = " + to_string(pManager->Game->Valid) + ", invalid = " + to_string(pManager->Game->InValid));
		}
	}
	else {
		pGUI->PrintMessage("Please Select Mode First To Start The Game");
	}
}