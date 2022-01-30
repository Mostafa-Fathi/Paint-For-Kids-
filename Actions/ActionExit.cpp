#include "ActionExit.h"

ActionExit::ActionExit(ApplicationManager* pApp) :Action(pApp) {

}

void ActionExit::Execute() {
	int returnedValue = MessageBox(NULL, "Do you want to save changes before exiting?", "Exit", MB_YESNOCANCEL);
	switch (returnedValue) {
		case IDYES:
		{
			//Action Save
		}
		case IDNO:
		{
			
		}
		case IDCANCEL:
		{

		}
	}

}