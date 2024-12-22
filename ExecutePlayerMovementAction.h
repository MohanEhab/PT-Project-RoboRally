#pragma once
#include "Action.h"
#include "Grid.h"
#include "Player.h"

class ExecutePlayerMovementAction : public Action {
public:
    ExecutePlayerMovementAction(ApplicationManager* pApp); 
    virtual ~ExecutePlayerMovementAction();                

    virtual void ReadActionParameters(); 
    virtual void Execute();             
};
