#include "ActionSelectMany.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\CMUgraphicsLib\colors.h"
#include <iostream>
#include "ActionDelete.h"

ActionSelectMany::ActionSelectMany(ApplicationManager* pApp) :Action(pApp) {}

//Execute the action
void ActionSelectMany::Execute() {
	bool continu = true;
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Select Muliple then press Delete to Delete Muliple Shapes ");

	while (continu)
	{
		int x, y;

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
				pGUI->SaveMessage(fig->GetDetails());
				fig->SetPreviousDrawColor(fig->GetDrawColor());
				fig->ChngDrawClr(MAGENTA);
				fig->SetSelected(true);
			}
			pManager->UpdateInterface();
		}
		else {
			continu = false;
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			if (ClickedItemOrder == ITM_DEL) {
				Action* DelMulti = new ActionDelete(pManager);
				DelMulti->Execute();
				delete DelMulti;
			}
			pManager->UnSelectAllFig();
			pGUI->ClearStatusBar();

		}
	}
	
}
