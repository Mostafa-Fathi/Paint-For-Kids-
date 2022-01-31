
#include "..\Actions/Action.h"
#include "..\ApplicationManager.h"


class ActionDrawColor :
	public Action
{
public:
	ActionDrawColor(ApplicationManager* pApp);

	virtual void Execute();
};

