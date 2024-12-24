#include "ToPlayModeAction.h"
#include "ApplicationManager.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
#include "ExecutePlayerMovementAction.h"
#include "SelectPlayerMovementAction.h"
#include "ShootingAction.h"
#include "AntennaAction.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}
void ToPlayModeAction::ReadActionParameters()
{}
ToPlayModeAction::~ToPlayModeAction() {}

void ToPlayModeAction::Execute() {
    Grid* pGrid = pManager->GetGrid(); 
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // Switch to Play Mode
    pOut->CreatePlayModeToolBar();
    pOut->PrintMessage("Switched to Play Mode!");


    do
    {
        //Antenna, to decide which player should start first
        AntennaAction AntennaAction(pManager);
        AntennaAction.Execute();


        //Movement Phase
    for (int i = 0; i < MaxPlayerCount; i++) {
        Player* currentPlayer = pGrid->GetCurrentPlayer();

        Command availableCommands[10];
        currentPlayer->DisplayRandomCommands(pGrid, availableCommands);

        pGrid->DisPlayerInfo();
        Command savedCommands[5] = {}; // empty arr for saved commands
        pOut->CreateCommandsBar(savedCommands, 0, availableCommands, 10);

        currentPlayer->SelectCommands(pGrid, availableCommands);

        Command* selectedCommands = currentPlayer->GetSavedCommands();
        int selectedCommandCount = currentPlayer->GetSavedCommandCount();
        pOut->CreateCommandsBar(selectedCommands, selectedCommandCount, availableCommands, 10);
        

        ExecutePlayerMovementAction executeAction(pManager);
        executeAction.Execute();

        

        pGrid->AdvanceCurrentPlayer();
        pGrid->DisPlayerInfo();

        if (pGrid->GetEndGame())
            break;
    }
    if (!pGrid->GetEndGame()) {
        pOut->PrintMessage("Movement Phase Completed. Click anywhere to enter Shooting Phase.");
        int x, y;
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
    }
    else
        break;

    // Shooting Phase
    ShootingAction shootingAction(pManager);
    shootingAction.Execute();
    pOut->ClearGridArea();
    pGrid->UpdateInterface();
    } while (!pGrid -> GetEndGame());
    

}
