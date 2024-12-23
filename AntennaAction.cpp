#include "AntennaAction.h"


AntennaAction :: AntennaAction(ApplicationManager* pApp) : Action(pApp) {}

AntennaAction::~AntennaAction() {}
 

void AntennaAction:: Execute(){

///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


// == Here are some guideline steps (numbered below) to implement this function ==

// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click

    // Get Output and Input interfaces
     Grid* pGrid = pManager->GetGrid();
     Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;
    // Ensure the antenna exists
    
    if (!pGrid->HasAntenna()) 
        return;
    
        // Print a message to notify the player
        pOut->PrintMessage("The antenna will decide the turn of players. Click to continue...");
        pIn->GetPointClicked(x, y); // Wait for the user to click
        pOut->ClearStatusBar();


        // Initialize players and distances
        Player* playerX = pGrid->GetCurrentPlayer(); // Get first player
        pGrid->AdvanceCurrentPlayer(); // Move to the second player
        Player* playerY = pGrid->GetCurrentPlayer(); // Get second player

        CellPosition playerXPos = playerX->GetCell()->GetCellPosition();
        CellPosition playerYPos = playerY->GetCell()->GetCellPosition();
        CellPosition antennaPos = pGrid->FindAntennaPosition();

        // Calculate distances for both players
        int playerXDistance = (playerXPos.VCell() > antennaPos.VCell()
            ? (playerXPos.VCell() - antennaPos.VCell())
            : (antennaPos.VCell() - playerXPos.VCell())) +
            (playerXPos.HCell() > antennaPos.HCell()
                ? (playerXPos.HCell() - antennaPos.HCell())
                : (antennaPos.HCell() - playerXPos.HCell()));

        int playerYDistance = (playerYPos.VCell() > antennaPos.VCell())
            ? (playerYPos.VCell() - antennaPos.VCell())
            : (antennaPos.VCell() - playerYPos.VCell()) +
            (playerYPos.HCell() > antennaPos.HCell())
            ?
            (playerYPos.HCell() - antennaPos.HCell())
            : (antennaPos.HCell() - playerYPos.HCell());

        // If both distances are equal
        if (playerXDistance == playerYDistance) {
            if (playerX->GetPlayerNumber() == 0) {
                pGrid->AdvanceCurrentPlayer(); // Player X goes first
                pOut->PrintMessage("Player" +to_string(playerX->GetPlayerNumber() + 1) + " will play first.Click anywhere to continue...");
                pIn->GetPointClicked(x, y);
                pOut->ClearStatusBar();
            }
            else {
                pOut->PrintMessage("Player" + to_string(playerY->GetPlayerNumber() + 1) + " will play first.Click anywhere to continue..."); //Player Y goes first
                pIn->GetPointClicked(x, y);
                pOut->ClearStatusBar();

            }
        }
        // If Player X's distance is lower
        else if (playerXDistance < playerYDistance) {
            pGrid->AdvanceCurrentPlayer(); // Player X goes first
            pOut->PrintMessage("Player" + to_string(playerX->GetPlayerNumber() + 1) + " will play first.Click anywhere to continue...");
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();

        }
        else
        {
            pOut->PrintMessage("Player" + to_string(playerY->GetPlayerNumber() + 1) + " will play first.Click anywhere to continue..."); //Player Y goes first
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();

        }
        // If Player Y's distance is lower, it will go first as we haven't changed the cuurent player integer
    
        // Notify the user about the first player============DONE
        
    }