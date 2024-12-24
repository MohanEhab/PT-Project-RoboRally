#include "UseToolKitAction.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
#include "ApplicationManager.h"

UseToolKitAction::UseToolKitAction(ApplicationManager* pApp) : Action(pApp)
{
}

void UseToolKitAction::ReadActionParameters()
{
    // No parameters to read for this action
}

void UseToolKitAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();   // Access the grid
    Player* currentPlayer = pGrid->GetCurrentPlayer(); // Get the current player

    if (!currentPlayer)
        return;

    currentPlayer->UseToolkit(pGrid); // Use the toolkit for the current player
}

UseToolKitAction::~UseToolKitAction()
{
}
