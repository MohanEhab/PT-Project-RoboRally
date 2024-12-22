#include "ExecutePlayerMovementAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Player.h"
#include "Input.h"
#include "Output.h"

ExecutePlayerMovementAction::ExecutePlayerMovementAction(ApplicationManager* pApp) : Action(pApp) {
}

ExecutePlayerMovementAction::~ExecutePlayerMovementAction() {
}

void ExecutePlayerMovementAction::ReadActionParameters() {
}

void ExecutePlayerMovementAction::Execute() {
    Grid* pGrid = pManager->GetGrid(); 
    Output* pOut = pGrid->GetOutput(); 

    Player* currentPlayer = pGrid->GetCurrentPlayer();

    if (!currentPlayer) {
        pOut->PrintMessage("No current player available to execute movement.");
        return;
    }

    Command* savedCommands = currentPlayer->GetSavedCommands();
    int savedCommandCount = currentPlayer->GetSavedCommandCount();

    if (savedCommandCount > 0) {
        currentPlayer->Move(pGrid, savedCommands);
        pOut->PrintMessage("Movement executed for the current player.");
    }
    else {
        pOut->PrintMessage("No saved commands available. Movement skipped.");
    }

    pOut->ClearStatusBar();
}