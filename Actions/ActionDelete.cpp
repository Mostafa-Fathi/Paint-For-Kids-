#include "ActionDelete.h"
ActionDelete::ActionDelete(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionDelete::Execute()
{
	pManager->DeleteSelectedFig();
}
