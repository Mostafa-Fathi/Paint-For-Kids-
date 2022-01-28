
#include "Figures/CFigure.h"
#include "Actions/Action.h"
#include "ApplicationManager.h"


class ActionResize :
	public Action
{
	CFigure* Selected;
public:
	ActionResize(ApplicationManager* pApp, CFigure*);

	//Reads ellipse parameters
	virtual void ReadActionParameters();

	//Add ellipse to the ApplicationManager
	virtual void Execute();
};

