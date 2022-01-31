#include "ActionSelect.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\CMUgraphicsLib\colors.h"
ActionSelect::ActionSelect(ApplicationManager* pApp) :Action(pApp) {}

//Execute the action
void ActionSelect::Execute() {

	GUI* pGUI = pManager->GetGUI();
	


	CFigure* fig = pManager->GetFigure(pManager->X, pManager->Y);
	if (fig != NULL) {
		if (fig->IsSelected())
		{
			pGUI->ClearStatusBar();
			fig->ChngDrawClr(fig->GetPreviousDrawColor());
			fig->SetSelected(false);
		}
		else
		{
			CFigure* selectedFigure = pManager->GetSelectedFigure();
			if (selectedFigure != NULL) {
				selectedFigure->ChngDrawClr(selectedFigure->GetPreviousDrawColor());
				selectedFigure->SetSelected(false);
			}
			pGUI->PrintMessage(fig->GetDetails());
			fig->SetPreviousDrawColor(fig->GetDrawColor());
			fig->ChngDrawClr(MAGENTA);
			fig->SetSelected(true);
		}
	}
	else {
		CFigure* selectedFigure = pManager->GetSelectedFigure();
		if (selectedFigure != NULL) {
			selectedFigure->ChngDrawClr(selectedFigure->GetPreviousDrawColor());
			selectedFigure->SetSelected(false);
			pGUI->ClearStatusBar();
		}
	}
}