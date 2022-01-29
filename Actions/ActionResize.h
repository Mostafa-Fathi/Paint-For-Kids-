
#include "../Figures/CFigure.h"
#include "Action.h"
#include "../ApplicationManager.h"


class ActionResize :
	public Action
{
	CFigure* Selected;
public:
	ActionResize(ApplicationManager* pApp);


	//Add ellipse to the ApplicationManager
	virtual void Execute();
};

