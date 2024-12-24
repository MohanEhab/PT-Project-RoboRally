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
    Grid* pGrid = pManager->GetGrid();
    Input* pInput = pGrid->GetInput();
    Output* pOutput = pGrid->GetOutput();

    // Ask the user to click on the target cell
    pOutput->PrintMessage("Click on the cell to paste the game object...");
    targetCell = pInput->GetCellClicked(); // Get the clicked cell position

    // Validate the target cell
    if (!targetCell.IsValidCell()) {
        pOutput->PrintMessage("Error: Selected cell is invalid!");
    }

    pOutput->ClearStatusBar();
}
void PasteObjectAction::Execute() {
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();
    Output* pOutput = pGrid->GetOutput();

    if (!targetCell.IsValidCell()) {
        pOutput->PrintMessage("Error: Selected cell is invalid!");
        return;
    }

    // Get the object from the clipboard
    GameObject* clipboardObject = pGrid->GetClipboard();

    if (!clipboardObject) {
        pOutput->PrintMessage("Clipboard is empty! Nothing to paste.");
        return;
    }
    GameObject* newObject = clipboardObject->Copy();
    newObject->SetPosition(targetCell); // Set the new position for the pasted object

    if (!pGrid->AddObjectToCell(newObject)) {
        delete newObject; // Clean up if the paste fails
        pOutput->PrintMessage("Failed to paste the game object: Cell is occupied.");
    }
    else {
        pOutput->PrintMessage("Game object pasted successfully!");
    }
}