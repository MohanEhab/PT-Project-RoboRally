#include "ToPlayModeAction.h"
#include "ApplicationManager.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
#include "ExecutePlayerMovementAction.h"
#include "SelectPlayerMovementAction.h"
#include "ShootingAction.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}
ToPlayModeAction::~ToPlayModeAction() {}

void ToPlayModeAction::ReadActionParameters() {}

void ToPlayModeAction::Execute() {
    Grid* pGrid = pManager->GetGrid(); 
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // Switch to Play Mode
    pOut->CreatePlayModeToolBar();
    pOut->PrintMessage("Switched to Play Mode!");


    do
    {
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

        // Step 6: Allow Shooting Phase
        //ShootingAction shootingAction(pManager);
        //shootingAction.Execute();

        pGrid->AdvanceCurrentPlayer();

    }

    pOut->PrintMessage("Round Completed. Click anywhere to continue.");
    int x, y;
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();
    } while (!pGrid -> GetEndGame());
    

}
