
#include "../Figures/CFigure.h"
#include "..\Actions/Action.h"
#include "..\ApplicationManager.h"


class ActionDrawColor :
	public Action
{
	CFigure* Selected;
public:
	ActionDrawColor(ApplicationManager* pApp);

	virtual void Execute();
};

