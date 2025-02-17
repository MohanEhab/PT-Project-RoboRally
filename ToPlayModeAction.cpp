#include "ToPlayModeAction.h"
#include "ApplicationManager.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
#include "ExecutePlayerMovementAction.h"
#include "SelectPlayerMovementAction.h"
#include "ShootingAction.h"
#include "AntennaAction.h"
#include "NewGameAction.h"
#include "UnifiedActionHandler.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}
void ToPlayModeAction::ReadActionParameters()
{}
ToPlayModeAction::~ToPlayModeAction() {}

void ToPlayModeAction::Execute() {
    
    Grid* pGrid = pManager->GetGrid(); 
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;
    // Switch to Play Mode
    pOut->CreatePlayModeToolBar();
    pOut->PrintMessage("Switched to Play Mode!Click to start.....");
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    do
    {
        //Antenna, to decide which player should start first
        AntennaAction AntennaAction(pManager);
        AntennaAction.Execute();
        
                                   
        //Movement Phase
        for (int i = 0; i < MaxPlayerCount; i++) {
            Player* currentPlayer = pGrid->GetCurrentPlayer();
            if (currentPlayer->shouldSkipThisTurn()) {
                pOut->PrintMessage("Player " + to_string(currentPlayer->GetPlayerNumber() + 1) + " is skipping this round.");
                currentPlayer->decrementSkipRounds(); // decrease the skip counter
                if (!currentPlayer->shouldSkipThisTurn()) {
                    currentPlayer->setActive(); // reset to active if no longer skipping
                }
                pGrid->AdvanceCurrentPlayer(); // move to the next player
                continue; // skip this player's turn
            }
            if (currentPlayer->HasHackDevice()) {
                UseHackAction useHackAction(pManager);
                useHackAction.Execute();

                currentPlayer->setSkipNextRound(1);

            }

            if (currentPlayer->HasToolkit()) {
                UseToolKitAction useToolkitAction(pManager);
                useToolkitAction.Execute();
                currentPlayer->setSkipNextRound(1);

            }

            if (currentPlayer->HasRebootnRepair()) {
                RebootAndRepairAction rebootAction(pManager);
                rebootAction.Execute();
                currentPlayer->setSkipNextRound(1);
            }

            Command availableCommands[10];
            currentPlayer->DisplayRandomCommands(pGrid, availableCommands);
            int availableCommandsCount = (currentPlayer->GetHealth() < 10) ? currentPlayer->GetHealth() : 10;

            pGrid->DisPlayerInfo();
            int extra = (currentPlayer->HasExtendedMemory()) ? 1 : 0;
            int maxCommands = 5 + extra;
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
            //Read user action

            pGrid->AdvanceCurrentPlayer();
            pGrid->DisPlayerInfo();
        }

            if (!pGrid->GetEndGame()) {
                pOut->PrintMessage("Movement Phase Completed. Click anywhere to enter Shooting Phase.");
                pIn->GetPointClicked(x, y);
                pOut->ClearStatusBar();
                
                
                // Shooting Phase
                ShootingAction shootingAction(pManager);
                shootingAction.Execute();

            }
            

    } while (!pGrid->GetEndGame());
            

        
}
