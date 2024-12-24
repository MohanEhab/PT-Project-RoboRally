#include "SaveGridAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
using namespace std;

SaveGridAction::SaveGridAction(ApplicationManager* pApp) :Action(pApp) {
    // Constructor initializes the ApplicationManager pointer
}


void SaveGridAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Enter the file name to save the grid: ");
    fileName = pIn->GetSrting(pOut); // get the file name as a string from the user
    pOut->ClearStatusBar(); // clear the status bar after input
}

void SaveGridAction::Execute()
{
    ReadActionParameters(); // read file name from the user
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    if (fileName.empty()) { // checks if  file name is empty
        pOut->PrintMessage("Error: File name cannot be empty!");
        return;
    }
    fileName += ".txt";//adds .txt to the file name to be saved as document
    ofstream OutFile(fileName); // Open file for writing
    if (!OutFile) { // Handle file opening errors
        pOut->PrintMessage("Error: Cannot open the file for saving!");
        return;
    }

    // call SaveAll for each type of GameObject in the required order
    pGrid->SaveAll(OutFile, 1); // Save Flags
    pGrid->SaveAll(OutFile, 2); // Save WaterPits
    pGrid->SaveAll(OutFile, 3); // Save DangerZones
    pGrid->SaveAll(OutFile, 4); // Save Belts
    pGrid->SaveAll(OutFile, 5); // Save Workshops
    pGrid->SaveAll(OutFile, 6); // Save Antennas
    pGrid->SaveAll(OutFile, 7); // Save RotatingGears

    OutFile.close(); //  Close the file after writing
    pOut->PrintMessage("Grid saved successfully!"); // Use the Output pointer
}

