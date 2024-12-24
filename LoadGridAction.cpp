#include "LoadGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
LoadGridAction::LoadGridAction(ApplicationManager* pApp) : Action(pApp) {
}

void LoadGridAction::ReadActionParameters() {
    // Get user input for the file name
    Grid* pGrid = pManager->GetGrid();
    Output* pOutput = pGrid->GetOutput();
    Input* pInput = pGrid->GetInput();

    pOutput->PrintMessage("Enter the file name to load the grid: ");
    fileName = pInput->GetSrting(pOutput); // Get file name from the user
    pOutput->ClearStatusBar();
}


void LoadGridAction::Execute() {
    ReadActionParameters(); // Step 1: Read file name
    Grid* pGrid = pManager->GetGrid();

    fileName += ".txt";
    ifstream inFile(fileName); // Open file for reading

    if (!inFile.is_open()) { // Handle file opening errors
        pGrid->GetOutput()->PrintMessage("Error: Cannot open the file!");
        return;
    }
    pGrid->ClearGrid();
    pGrid->LoadAll(inFile); // Step 2: Call LoadAll to load objects
    inFile.close();         // Step 3: Close the file

    pGrid->GetOutput()->PrintMessage("Grid loaded successfully!");
}
