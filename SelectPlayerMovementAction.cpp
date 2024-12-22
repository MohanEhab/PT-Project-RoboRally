#include "SelectPlayerMovementAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Player.h"
#include "Input.h"
#include "Output.h"

SelectPlayerMovementAction::SelectPlayerMovementAction(ApplicationManager* pApp) : Action(pApp) {
}

SelectPlayerMovementAction::~SelectPlayerMovementAction() {
}

void SelectPlayerMovementAction::ReadActionParameters() {
}

void SelectPlayerMovementAction::Execute() {
    Grid* pGrid = pManager->GetGrid(); 
    Output* pOut = pGrid->GetOutput(); 
    Input* pIn = pGrid->GetInput();  

    Player* currentPlayer = pGrid->GetCurrentPlayer();

    if (!currentPlayer) {
        pOut->PrintMessage("No current player available to select movement.");
        return;
    }

    Command availableCommands[10];
    currentPlayer->DisplayRandomCommands(pGrid, availableCommands);

    currentPlayer->SelectCommands(pGrid, availableCommands);

    Command* savedCommands = currentPlayer->GetSavedCommands();
    int savedCommandCount = currentPlayer->GetSavedCommandCount();

    if (savedCommandCount > 0) {
        currentPlayer->Move(pGrid, savedCommands);
    }
    else {
        pOut->PrintMessage("No commands selected. Movement skipped.");
    }

    pOut->ClearStatusBar();
}
