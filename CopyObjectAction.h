#pragma once
#include "Action.h"
#include "Grid.h"
#include "CellPosition.h"
class CopyObjectAction :public Action
{
	CellPosition sourcecell;//Stores the position of the cell where the user wants to copy the game object from
public:
	CopyObjectAction(ApplicationManager* pApp); //constructor have access to the aplicationmanager ex the grid so it can access cell and game object
	virtual void ReadActionParameters();        // gets the input
	virtual void Execute();                     // Perform the copy
};

