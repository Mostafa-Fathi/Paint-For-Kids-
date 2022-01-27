
#include "Figures/CFigure.h"
#include "Actions/Action.h"
#include "ApplicationManager.h"


class ResizeAction :
	public Action
{
	CFigure* Selected;
public:
	ResizeAction(ApplicationManager* pApp, CFigure*);

	//Reads ellipse parameters
	virtual void ReadActionParameters();

	//Add ellipse to the ApplicationManager
	virtual void Execute();
};

