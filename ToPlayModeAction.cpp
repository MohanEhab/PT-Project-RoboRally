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
    Input* pIn = pGrid->GetInput(); 
    pOut->CreatePlayModeToolBar();

    Player* currentPlayer = pGrid->GetCurrentPlayer();

    Command availableCommands[10];
    currentPlayer->DisplayRandomCommands(pGrid, availableCommands);
    pGrid->DisPlayerInfo();
    Command savedCommands[5] = {}; // empty saved, full av
    pOut->CreateCommandsBar(savedCommands, 0, availableCommands, 10);

    currentPlayer->SelectCommands(pGrid, availableCommands); //allow selection

    Command* selectedCommands = currentPlayer->GetSavedCommands();
    int selectedCommandCount = currentPlayer->GetSavedCommandCount();
    pOut->CreateCommandsBar(selectedCommands, selectedCommandCount, availableCommands, 10);
    
}


