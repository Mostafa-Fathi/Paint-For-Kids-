#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class ActionDelete :
    public Action
{
public:

    ActionDelete(ApplicationManager* pApp);

    // Inherited via Action
    virtual void Execute() ;
};

