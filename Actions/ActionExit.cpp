#include "..\ApplicationManager.h"
#include "ActionExit.h"
#include "ActionSave.h"


ActionExit::ActionExit(ApplicationManager* pApp) :Action(pApp) {

}

void ActionExit::Execute() {
	if (pManager->getFigCount() > 0)
	{
		int returnedValue = MessageBox(NULL, "Do you want to save changes before exiting?", "Exit", MB_ICONWARNING | MB_YESNO);
		switch (returnedValue) {
		case IDYES:
		{
			ActionSave* save = new ActionSave(pManager);
			save->Execute();
			delete save;
		}
		}
		pManager->ClearFigList();
	}
}