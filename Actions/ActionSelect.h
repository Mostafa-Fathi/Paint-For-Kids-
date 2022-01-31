#define ACTION_SELECT_H

#include "Action.h"

//select figure action class
class ActionSelect : public Action {
public:
	ActionSelect(ApplicationManager* pApp);


	//select the figure and highlight it
	virtual void Execute();
};