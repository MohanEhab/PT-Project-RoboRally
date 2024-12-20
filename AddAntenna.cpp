#include "AddAntenna.h"


AddAntenna::AddAntenna(ApplicationManager* pApp) : Action(pApp) {}


void AddAntenna::ReadActionParameters() {
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


		// == Here are some guideline steps (numbered below) to implement this function ==

		// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	// 2- Read the 	AntennaPos
	
	//Validate first if there is another Antenna
	if (pGrid->HasAntenna()) //New function implemented in Grid.cpp to check if the whole grid has a flag or not
	{
		pOut->PrintMessage("Error: An Antenna already exists on the grid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		AntennaPos = CellPosition(-1, -1); // Invalidate flag position
		return;
	}
	
	pOut->PrintMessage("Click on the cell to place the Antenna.");
	AntennaPos = pIn->GetCellClicked();

	

	if (!AntennaPos.IsValidCell())
	{
		pOut->PrintMessage("Error: Selected cell is not valid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		AntennaPos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	if (!pGrid->IsCellEmpty(AntennaPos)) {
		pOut->PrintMessage("Error: Selected cell already contains a game object. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		AntennaPos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}

	if (AntennaPos.GetCellNum() == 1 || AntennaPos.GetCellNum() == 55) // Check if start cell is the first cell
	{
		pOut->PrintMessage("Error: Start cell cannot be the first cell. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		AntennaPos = CellPosition(-1, -1); // Invalidate start position
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	
	// 4- Make the needed validations on the read parameters=======DONE up

	// 5- Clear status bar
	pOut->ClearStatusBar();
}


void AddAntenna::Execute() {

	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();


	if (!AntennaPos.IsValidCell())
		return;//that fixed the problem of executing

	// Create a belt object with the parameters read from the user

	
	Antenna* pAntenna = new Antenna(AntennaPos);
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager


	bool added = pGrid->AddObjectToCell(pAntenna);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Failed to Add! Click to continue ...");
	}
	// Here, the belt is created and added to the GameObject of its Cell, so we finished executing the AddBeltAction
}

AddAntenna::~AddAntenna()
{
}