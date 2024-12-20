#include "AddWaterPit.h"

AddWaterPit::AddWaterPit(ApplicationManager* pApp) : Action(pApp) {}


void AddWaterPit::ReadActionParameters() {
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	// 2- Read the Waterpos
	pOut->PrintMessage("Click on the cell to place the water pit.");
	Waterpos = pIn->GetCellClicked();
	// 4- Make the needed validations on the read parameters
	if (!Waterpos.IsValidCell())
	{
		pOut->PrintMessage("Error: Selected cell is not valid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		Waterpos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}

	if (Waterpos.GetCellNum() == 1 || Waterpos.GetCellNum() == 55)
	{
		pOut->PrintMessage("Error: Water pit cannot be placed in the first or last cell. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		Waterpos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}

	if (!pGrid->IsCellEmpty(Waterpos))
	{
		pOut->PrintMessage("Error: Selected cell already contains a game object. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		Waterpos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddWaterPit::Execute() {
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	if (!Waterpos.IsValidCell())
		return;

	// 1-Create a water object
	WaterPit* pWaterPit = new WaterPit(Waterpos);
	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	// 3-Add the water object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pWaterPit);
	// 4-Check if the water was added and print an errror message if flag couldn't be added
	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to Add! Click to continue...");
	}
}

AddWaterPit::~AddWaterPit()
{
}