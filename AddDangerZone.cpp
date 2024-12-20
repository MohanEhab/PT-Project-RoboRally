#include "AddDangerZone.h"


AddDangerZone::AddDangerZone(ApplicationManager* pApp) : Action(pApp) {
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddDangerZone::ReadActionParameters() {

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	// 2- Read the dangerzonePos
	pOut->PrintMessage("Click on the cell to place the danger zone.");
	DangerZonePos = pIn->GetCellClicked();
	// 4- Make the needed validations on the read parameters
	if (!DangerZonePos.IsValidCell()) {
		pOut->PrintMessage("Error: Selected cell is not valid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		DangerZonePos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	if (DangerZonePos.GetCellNum() == 1 || DangerZonePos.GetCellNum() == 55) {
		pOut->PrintMessage("Error: Danger zone cannot be placed in the first or last cell. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		DangerZonePos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}

	if (!pGrid->IsCellEmpty(DangerZonePos)) {
		pOut->PrintMessage("Error: Selected cell already contains a game object. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		DangerZonePos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddDangerZone::Execute() {
	// The first line of any Action Execution is to read its parameter first 
		// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	if (!DangerZonePos.IsValidCell())
		return;
	// 1-Create a dangerzone object
	DangerZone* pDangerZone = new DangerZone(DangerZonePos);
	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	// 3-Add the dangerzone object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pDangerZone);

	// 4-Check if the dangerzone was added and print an errror message if dangerzone couldn't be added
	if (!added) {
		pGrid->PrintErrorMessage("Error: Failed to Add! Click to continue...");
	}
}
AddDangerZone::~AddDangerZone()
{
}