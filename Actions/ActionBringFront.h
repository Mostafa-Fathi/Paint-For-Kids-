
#include "Action.h"
#include "../Figures/CFigure.h"
#include "../ApplicationManager.h"



class ActionBringFront :
	public Action
{
	CFigure* Selected;
	int Index;
public:
	ActionBringFront(ApplicationManager* pApp);

	//Add ellipse to the ApplicationManager
	virtual void Execute();
};