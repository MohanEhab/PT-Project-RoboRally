#pragma once

#include "Action.h"
#include "CellPosition.h"
class PasteObjectAction : public Action {
private:
    CellPosition targetCell; // The cell where the object will be pasted

public:
    PasteObjectAction(ApplicationManager* pApp); // Constructor

    virtual void ReadActionParameters(); // Reads parameters for the action
    virtual void Execute();              // Executes the paste 
};

