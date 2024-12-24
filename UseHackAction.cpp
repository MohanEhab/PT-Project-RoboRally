#include "UseHackAction.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
#include "ApplicationManager.h"

UseHackAction::UseHackAction(ApplicationManager* pApp) : Action(pApp)
{
}

void UseHackAction::ReadActionParameters()
{
    // No parameters to read for this action
}

void UseHackAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();       // Access the grid
    Player* currentPlayer = pGrid->GetCurrentPlayer(); // Get the current player

    if (!currentPlayer)
        return;

    currentPlayer->UseHackDevice(pGrid);    // Use the hack device for the current player
}

UseHackAction::~UseHackAction()
{
}
