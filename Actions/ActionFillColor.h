
#include "..\Actions/Action.h"
#include "..\ApplicationManager.h"


class ActionFillColor :
	public Action
{
public:
	ActionFillColor(ApplicationManager* pApp);

	virtual void Execute();
};

