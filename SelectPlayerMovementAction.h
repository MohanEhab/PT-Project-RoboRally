#pragma once
#include "Action.h"
#include "Grid.h"
#include "Player.h"

class SelectPlayerMovementAction : public Action {
public:
    SelectPlayerMovementAction(ApplicationManager* pApp); 
    virtual ~SelectPlayerMovementAction();                

    virtual void ReadActionParameters(); 
    virtual void Execute();              
};
