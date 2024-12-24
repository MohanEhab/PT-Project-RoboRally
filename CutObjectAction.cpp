#include "CutObjectAction.h"
#include "CopyObjectAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"
#include "CellPosition.h"
#include "Belt.h"


CutObjectAction::CutObjectAction(ApplicationManager* pApp) :Action(pApp)
{
    // Initializes the pManager pointer of Action with the passed pointer
}

void CutObjectAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();;// gets access to the grid using pmanager(which acts as the main controller for the application)
    Input* pInput = pGrid->GetInput();// Access input to get position cliclked
    Output* pOutput = pGrid->GetOutput();// access output to display feedback to the user

    pOutput->PrintMessage("Click on the cell to cut the game object...");
    sourceCell = pInput->GetCellClicked();// gets the clicked cell and stores it in sourcecell

    if (!sourceCell.IsValidCell()) {// checks if the cell is valid
        pOutput->PrintMessage("Error: Selected cell is invalid!");
    }

    pOutput->ClearStatusBar();//remove the massage displayed
}

void CutObjectAction::Execute() {
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();
    Input* pInput = pGrid->GetInput();// Access input to get position cliclked
    Output* pOutput = pGrid->GetOutput();
    int x, y;
    if (!sourceCell.IsValidCell()) {
        pOutput->PrintMessage("Error: Selected cell is invalid,click anywhere to contiune");
        pInput->GetPointClicked(x, y); // Wait for user to click
        pOutput->ClearStatusBar(); // Clear the status bar after click
        return;
    }

    GameObject* pGameObject = pGrid->GetObjectFromCell(sourceCell);
    if (!pGameObject) {
        pOutput->PrintMessage("No game object found in the selected cell,click anywhere to contiune");
        pInput->GetPointClicked(x, y); // Wait for user to click
        pOutput->ClearStatusBar(); // Clear the status bar after click
        return;
    }
    if (pGameObject->GetType() == 4) {
        pOutput->PrintMessage("Belts cannot be cut,click anywhere to contiune");
        pInput->GetPointClicked(x, y); // Wait for user to click
        pOutput->ClearStatusBar(); // Clear the status bar after click
        return;
    }

    pGameObject = pGrid->RemoveObjectFromCell(sourceCell);
    // Store the object in the clipboard
    pGrid->SetClipboard(pGameObject);

    pOutput->PrintMessage("Game object cut successfully!");
  

}