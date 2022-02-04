#include "ActionSelectMany.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\CMUgraphicsLib\colors.h"

ActionSelectMany::ActionSelectMany(ApplicationManager* pApp) :Action(pApp) {}

//Execute the action
void ActionSelectMany::Execute() {
	bool continu = true;
	while (continu)
	{
		int x, y;

		GUI* pGUI = pManager->GetGUI();

		pGUI->GetPointClicked(x, y);
		CFigure* fig = pManager->GetFigure(x, y);

		if (fig != NULL) {
			int figSelected = 0;
			if (fig->IsSelected())
			{
				pGUI->ClearStatusBar();
				fig->SetSelected(false);
				fig->ChngDrawClr(fig->GetPreviousDrawColor());
			}
			else
			{
				CFigure* selectedFigure = pManager->GetSelectedFigure();
				pGUI->PrintMessage(fig->GetDetails());
				fig->SetPreviousDrawColor(fig->GetDrawColor());
				fig->ChngDrawClr(MAGENTA);
				fig->SetSelected(true);
			}
			pManager->UpdateInterface();
		}
		else {
			continu = false;
			pManager->UnSelectAllFig();
			pGUI->ClearStatusBar();

		}
	}
	
}
