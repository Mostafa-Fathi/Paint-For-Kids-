
#include "../Figures/CFigure.h"
#include "..\Actions/Action.h"
#include "..\ApplicationManager.h"


class ActionFillColor :
	public Action
{
	CFigure* Selected;
public:
	ActionFillColor(ApplicationManager* pApp);

	virtual void Execute();
};

