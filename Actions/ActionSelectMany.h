#define ACTION_SELECT_H

#include "Action.h"

//select figure action class
class ActionSelectMany : public Action {
public:
	ActionSelectMany(ApplicationManager* pApp);

	//select the figure and highlight it
	virtual void Execute();
};