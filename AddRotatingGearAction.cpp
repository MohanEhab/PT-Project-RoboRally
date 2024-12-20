#include "AddRotatingGearAction.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager* pApp) :Action(pApp)
{ 
}

void AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	// 2- Read the gearPos
	pOut->PrintMessage("Click on the cell to place the rotating gear.");
	gearPos = pIn->GetCellClicked();

	if (!gearPos.IsValidCell())
	{
		pOut->PrintMessage("Error: Selected cell is not valid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		gearPos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	if (!pGrid->IsCellEmpty(gearPos)) {
		pOut->PrintMessage("Error: Selected cell already contains a game object. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		gearPos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}

	if (gearPos.GetCellNum() == 1 || gearPos.GetCellNum() == 55) // Check if start cell is the first cell
	{
		pOut->PrintMessage("Error: Start cell cannot be the first cell. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		gearPos = CellPosition(-1, -1); // Invalidate start position
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	// 3- Read whether the direction will be clockwise or not
	pOut->PrintMessage("Enter the direction (C for clockwise, A for anti-clockwise):");
	string direction = pIn->GetSrting(pOut);
	if (direction == "C" || direction == "c")
		clockwise = true;
	else if (direction == "A" || direction == "a")
		clockwise = false;
	else
	{
		pOut->PrintMessage("Error: Invalid direction entered. Click anywhere to continue...");
		pIn->GetPointClicked(x, y);
		gearPos = CellPosition(-1, -1);
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	// 4- Make the needed validations on the read parameters=======DONE up
	
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	if (!gearPos.IsValidCell())
		return;
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	// 1-Create a rotating gear object
	RotatingGear* pRotatingGear = new RotatingGear(gearPos, clockwise);
	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	// 3-Add the rotating object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pRotatingGear);
	// 4-Check if the rotating gear was added and print an errror message if flag couldn't be added
	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to Add! Click to continue...");
	}
}
AddRotatingGearAction::~AddRotatingGearAction()
{
}