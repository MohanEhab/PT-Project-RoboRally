#include "DeleteGameObjectAction.h"
#include "Grid.h"
#include "CellPosition.h"
#include "GameObject.h"
#include "Output.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) :Action(pApp), pos(-1, -1)
{
    // Initializes the pManager pointer of Action with the passed pointer
}

void DeleteGameObjectAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();//: Captures the grid cell where the user wants to delete a game object.
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    //Displays a message in the status bar
    pOut->PrintMessage("Click on the cell to delete the game object");
    pos = pIn->GetCellClicked();// wait for user to click
    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell! Action aborted.");
        pos = CellPosition(-1, -1);// reset pos to indicate invalid input
        return;// checks if the position is valid or not
    }

    pOut->ClearStatusBar();
}

void DeleteGameObjectAction::Execute() {
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();//: Captures the grid cell where the user wants to delete a game object.
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;
    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Error: Selected cell is invalid,click anywhere to contiune");
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
        return;
    }

    // Use Grid's method to remove the object
    GameObject* pGameObject = pGrid->RemoveObjectFromCell(pos);

    if (!pGameObject) {
        pOut->PrintMessage("No game object found in the selected cell,click anywhere to contiune");
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
        return;
    }

    // Delete the object
    delete pGameObject;

    pOut->PrintMessage("Game object deleted successfully,click anywhere to contiune");
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();
}