#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Workshop.h"
class AddWorkshop :public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition WorkshopPos; // 1- The position of Water Pit Pos
public:
	AddWorkshop(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads action parameters 
	virtual void Execute(); // Creates a new rotating gear Object 
	// then Sets this rotating gear object to the GameObject Pointer of its Cell
	virtual ~AddWorkshop();
};


