#include "ToPlayModeAction.h"
#include "ApplicationManager.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}
ToPlayModeAction::~ToPlayModeAction() {}

void ToPlayModeAction::ReadActionParameters()
{
}

void ToPlayModeAction::Execute() {
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    pOut->CreatePlayModeToolBar();

    Player* currentPlayer = pGrid->GetCurrentPlayer();

    // Generate and display random available commands
    Command availableCommands[10];
    currentPlayer->DisplayRandomCommands(pGrid, availableCommands);
    pGrid->DisPlayerInfo();
    // Draw the command bar with empty saved commands and generated available commands
    Command savedCommands[5] = {}; // Initially empty
    pOut->CreateCommandsBar(savedCommands, 0, availableCommands, 10);

    // Allow the player to select commands
    currentPlayer->SelectCommands(pGrid, availableCommands);

    // Update saved commands bar after selection
    Command* selectedCommands = currentPlayer->GetSavedCommands();
    int selectedCommandCount = currentPlayer->GetSavedCommandCount();
    pOut->CreateCommandsBar(selectedCommands, selectedCommandCount, availableCommands, 10);
}


