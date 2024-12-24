#include "CopyObjectAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"
#include "CellPosition.h"
#include "Flag.h"
#include "Antenna.h"
#include "Belt.h"


CopyObjectAction::CopyObjectAction(ApplicationManager* pApp) :Action(pApp)
{
    // Initializes the pManager pointer of Action with the passed pointer
}

void CopyObjectAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();// gets access to the grid using pmanager(which acts as the main controller for the application)
    Input* pInput = pGrid->GetInput(); // Access input to get position cliclked
    Output* pOutput = pGrid->GetOutput();// access outpout to display feedback to the user
   
    pOutput->PrintMessage("Click on the cell to copy the game object from");
    sourcecell = pInput->GetCellClicked();      // gets the clicked cell and stores it in sourcecell
    pOutput->ClearStatusBar();                  // remove the massage displayed
}

void CopyObjectAction::Execute() {
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();
    Input* pInput = pGrid->GetInput(); // Access input to get position cliclked
    Output* pOutput = pGrid->GetOutput();
    int x, y;
    if (!sourcecell.IsValidCell()) {
        pOutput->PrintMessage("Error: Selected cell is invalid,click anywhere to contiune");
        pInput->GetPointClicked(x, y); // Wait for user to click
        pOutput->ClearStatusBar(); // Clear the status bar after click
        return;
    }

    // Use Grid's method to get the object (without removing it)
    GameObject* pGameObject = pGrid->GetObjectFromCell(sourcecell);

    if (!pGameObject) {
        pOutput->PrintMessage("No game object found in the selected cell,click anywhere to continue");
        pInput->GetPointClicked(x, y); // Wait for user to click
        pOutput->ClearStatusBar(); // Clear the status bar after click
        return;
    }

    if (pGameObject->GetType() == 1 || pGameObject->GetType() == 6 || pGameObject->GetType() == 4) {//makes sure that anntena and belt and flag cannot be copped using get type
        pOutput->PrintMessage("Flags, Antennas, and Belts cannot be copied,click anywhere to contiune");
        pInput->GetPointClicked(x, y); // Wait for user to click
        pOutput->ClearStatusBar(); // Clear the status bar after click
        return;
    }

    // Store the object in the clipboard
    pGrid->SetClipboard(pGameObject->Copy()); // copy the object for independent copy

    pOutput->PrintMessage("Game object copied successfully!");
}
