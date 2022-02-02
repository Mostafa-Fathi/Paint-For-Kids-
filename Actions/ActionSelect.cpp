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
			fig->SetSelected(false);
			fig->ChngDrawClr(fig->GetPreviousDrawColor());
		}
		else
		{
			CFigure* selectedFigure = pManager->GetSelectedFigure();
			if (selectedFigure != NULL) {
				selectedFigure->SetSelected(false);
				selectedFigure->ChngDrawClr(selectedFigure->GetPreviousDrawColor());
				
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
			selectedFigure->SetSelected(false);
			selectedFigure->ChngDrawClr(selectedFigure->GetPreviousDrawColor());
			pGUI->ClearStatusBar();
		}
	}
}