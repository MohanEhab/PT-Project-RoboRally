#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Antenna.h"
class AddAntenna :public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition AntennaPos; // 1- The position of Water Pit Pos
public:
	AddAntenna(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads action parameters 
	virtual void Execute(); // Creates a new rotating gear Object 
	// then Sets this rotating gear object to the GameObject Pointer of its Cell
	virtual ~AddAntenna();
};



