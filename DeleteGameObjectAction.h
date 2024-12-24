#pragma once
#include "Action.h"

class DeleteGameObjectAction : public Action {
    CellPosition pos; // To store the clicked position
public:
    DeleteGameObjectAction(ApplicationManager* pApp); // constructor have access to the aplicationmanager 
    virtual void ReadActionParameters(); // Reads the cell  that will be deleted
    virtual void Execute();              // Deletes the game object

};

