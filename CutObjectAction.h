#pragma once
#include "Action.h"
#include "CellPosition.h"

class CutObjectAction : public Action {
private:
    CellPosition sourceCell; // The position of the cell to cut from

public:
    CutObjectAction(ApplicationManager* pApp);

    virtual void ReadActionParameters(); // Reads parameters for the action
    virtual void Execute();              // Executes the cut 

};