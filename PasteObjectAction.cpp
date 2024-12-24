#include "PasteObjectAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "GameObject.h"
#include"Belt.h"



PasteObjectAction::PasteObjectAction(ApplicationManager* pApp) :Action(pApp)
{
    // Initializes the pManager pointer of Action with the passed pointer
}

void PasteObjectAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();//: Captures the grid cell where the user wants to delete a game object.
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // Ask the user to click on the target cell
    pOut->PrintMessage("Click on the cell to paste the game object...");
    targetCell = pIn->GetCellClicked(); // Get the clicked cell position

    // Validate the target cell
    if (!targetCell.IsValidCell()) {
        pOut->PrintMessage("Error: Selected cell is invalid!");
    }

    pOut->ClearStatusBar();
}
void PasteObjectAction::Execute() {
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();//: Captures the grid cell where the user wants to delete a game object.
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;
    if (!targetCell.IsValidCell()) {
        pOut->PrintMessage("Error: Selected cell is invalid,clcik anywhere to contiune");
        pIn->GetPointClicked(x, y); // Wait for user to click
        pOut->ClearStatusBar(); // Clear the status bar after click
        return;
    }

    // Get the object from the clipboard
    GameObject* clipboardObject = pGrid->GetClipboard();

    if (!clipboardObject) {
        pOut->PrintMessage("Clipboard is empty Nothing to paste,click anywhere to contiune");
        pIn->GetPointClicked(x, y); // Wait for the user to click
        pOut->ClearStatusBar();
        return;
    }
    GameObject* newObject = clipboardObject->Copy();
    newObject->SetPosition(targetCell); // Set the new position for the pasted object

    if (!pGrid->AddObjectToCell(newObject)) {
        delete newObject; // Clean up if the paste fails
        pOut->PrintMessage("Cannot paste cell contains gameobject,click anywhere to contiune");
        pIn->GetPointClicked(x, y); // Wait for the user to click
        pOut->ClearStatusBar();
    }
    else {
        pOut->PrintMessage("Game object pasted successfully,click anywhere to contiune");
        pIn->GetPointClicked(x, y); // Wait for the user to click
        pOut->ClearStatusBar();
    }
}