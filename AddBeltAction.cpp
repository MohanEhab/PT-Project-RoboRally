#include "AddBeltAction.h"
AddBeltAction::AddBeltAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddBeltAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;

	// Read the startPos parameter
	pOut->PrintMessage("New Belt: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	
	if (!startPos.IsValidCell()) //start Pos validation
	{
		pOut->PrintMessage("Error: Start cell is not valid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	if (startPos.GetCellNum() == 1 ) // Check if start cell is the first cell
	{
		pOut->PrintMessage("Error: Start cell cannot be the first cell. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		startPos = CellPosition(-1, -1);
		return;
	}
	if ( startPos.GetCellNum() == 55) // Check if start cell is the first cell
	{
		pOut->PrintMessage("Error: Start cell cannot be the last cell. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		startPos = CellPosition(-1, -1);
		return;
	}

	if (!pGrid->IsCellEmpty(startPos)) // Check if start cell already contains an object
	{
		pOut->PrintMessage("Error: Start cell already contains a game object. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		startPos = CellPosition(-1, -1);
		return;
	}

	//test if startPos is an EndPos of another Belt
	for (int i = 0; i < NumVerticalCells; ++i) {
		for (int j = 0; j < NumHorizontalCells; ++j) { //Go through every single cell on the grid
			CellPosition currentPos(i, j); //created a position for each cell to test them and check if there's any belt in the grid
			Belt* existingBelt = pGrid->GetNextBelt(currentPos);

			// If a belt exists at this cell and its end position matches the start position of the new belt
			if (existingBelt != NULL) { //if a belt exists, as the GetNextBelt() func returns NULL if not

				CellPosition existingBeltEnd = existingBelt->GetEndPosition();
				if (existingBeltEnd.VCell() == startPos.VCell() && existingBeltEnd.HCell() == startPos.HCell()) { //existingBelt End Pos = startpos 
					pOut->PrintMessage("Error: Start cell cannot be the end position of an existing belt. Click anywhere to continue...");
					pIn->GetPointClicked(x, y); // Wait for user to click
					pOut->ClearStatusBar();
					startPos = CellPosition(-1, -1);
					endPos = CellPosition(-1, -1);
					return;
				}
			}
		}
	}

	// Read the endPos parameter
	pOut->PrintMessage("New Belt: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	if (!endPos.IsValidCell()) //end Pos validation
	{
		pOut->PrintMessage("Error: End cell is not valid. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		return;
	}
	if (!pGrid->IsCellEmpty(endPos)) // Check if end cell already contains an object
	{
		pOut->PrintMessage("Error: End cell already contains a game object. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		startPos = CellPosition(-1, -1);
		return;
	}


	if (!(startPos.HCell() == endPos.HCell() || startPos.VCell() == endPos.VCell())) //validate the belt positions are in the same row or column
	{
		pOut->PrintMessage("Error: Start and End cells must be in the same row or column. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		startPos = CellPosition(-1, -1);
		endPos = CellPosition(-1, -1);
		return;
	}


	Cell* endCell = pGrid->GetCell(endPos);  
	if (endCell->HasFlag())
	{
		pOut->PrintMessage("Error: End cell contains a flag. Click anywhere to continue...");
		pIn->GetPointClicked(x, y); // Wait for user to click
		pOut->ClearStatusBar(); // Clear the status bar after click
		endPos = CellPosition(-1, -1);
		return;
	}
	
	
	///TODO: Make the needed validations on the read parameters



	// Clear messages
	pOut->ClearStatusBar();
}

void AddBeltAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	
	if (!startPos.IsValidCell() || !endPos.IsValidCell())
		return;//that fixed the problem of executing

	// Create a belt object with the parameters read from the user
	
	Belt * pBelt = new Belt(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

										
	bool added = pGrid->AddObjectToCell(pBelt);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Failed to Add! Click to continue ...");
	}
	// Here, the belt is created and added to the GameObject of its Cell, so we finished executing the AddBeltAction
	

}

AddBeltAction::~AddBeltAction()
{
}
