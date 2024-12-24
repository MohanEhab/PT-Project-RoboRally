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
        int availableCommandsCount = (currentPlayer->GetHealth() < 10) ? currentPlayer->GetHealth() : 10;

        pGrid->DisPlayerInfo();
        int extra = (currentPlayer->HasExtendedMemory()) ? 1 : 0;
        int maxCommands =  5 + extra;
        Command* savedCommands = new Command[maxCommands]; // store player's selected commands
        pOut->CreateCommandsBar(savedCommands, 0, availableCommands, availableCommandsCount);

        currentPlayer->SelectCommands(pGrid, availableCommands);

        Command* selectedCommands = currentPlayer->GetSavedCommands();
        int selectedCommandCount = currentPlayer->GetSavedCommandCount();
        pOut->CreateCommandsBar(selectedCommands, selectedCommandCount, availableCommands, availableCommandsCount);
        

        ExecutePlayerMovementAction executeAction(pManager);
        executeAction.Execute();
        
        if (currentPlayer->HasExtendedMemory()) {
            currentPlayer->disableExtendedMemory();
        }


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
