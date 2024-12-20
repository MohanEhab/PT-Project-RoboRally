#include "AddFlagAction.h"



AddFlagAction::AddFlagAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddFlagAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	// 2- Read the flagPos
	
	//Validate first if there are other flags
	if (pGrid->HasFlag()) //New function implemented in Grid.cpp to check if the whole grid has a flag or not
	{
		pOut->PrintMessage("Error: A flag already exists on the grid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		flagPos = CellPosition(-1, -1); // Invalidate flag position
		return;
	}
	
	
	pOut->PrintMessage("Click on the cell to place the flag.");
	flagPos = pIn->GetCellClicked();
	
	// 4- Make the needed validations on the read parameters
	if (!flagPos.IsValidCell())
	{
		pOut->PrintMessage("Error: Selected cell is not valid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		flagPos = CellPosition(-1, -1); // Invalidate flag position
		return;
	}

	if (!pGrid -> IsCellEmpty(flagPos)) //new function implemented in Grid.cpp to check if the cell we're on does not have any objects
	{
		pOut->PrintMessage("Error: Selected cell already contains a game object. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		flagPos = CellPosition(-1, -1); // Invalidate flag position
		return;
	}

	if (flagPos.GetCellNum() == 1 || flagPos.GetCellNum() == 55) // Check if start cell is the first cell
	{
		pOut->PrintMessage("Error: Start cell cannot be the first cell. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		flagPos = CellPosition(-1, -1); // Invalidate flag position
		return;
	}
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddFlagAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	if (!flagPos.IsValidCell())
		return;//that fixed the problem of executing
	// 1-Create a flag object
	Flag* pFlag = new Flag(flagPos);

	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();

	// 3-Add the flag object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pFlag);
	
	// 4-Check if the flag was added and print an errror message if flag couldn't be added
	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to Add! Click to continue...");
	}

}

AddFlagAction::~AddFlagAction()
{
}