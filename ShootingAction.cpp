#include "ShootingAction.h"
#include "Cell.h"
ShootingAction::ShootingAction(ApplicationManager* pApp) :Action(pApp)
{
}

ShootingAction::~ShootingAction()
{
}
void ShootingAction::ReadActionParameters() {
}

void ShootingAction::Execute() {
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;
    if (!pGrid->GetEndGame()) {
        Player* playerX = pGrid->GetCurrentPlayer();
        pGrid->AdvanceCurrentPlayer();
        Player* playerY = pGrid->GetCurrentPlayer();

        // Store player numbers for clarity in messages
        int playerXNumber = playerX->GetPlayerNumber() + 1;
        int playerYNumber = playerY->GetPlayerNumber() + 1;

        // Get positions and directions of both players
        CellPosition playerXPos = playerX->GetCell()->GetCellPosition();
        CellPosition playerYPos = playerY->GetCell()->GetCellPosition();

        Direction playerXDirection = playerX->GetDirection();
        Direction playerYDirection = playerY->GetDirection();


        //////////////////////////////////////////////////////////////////////////
        //Drawing calculations 
       // Calculate StartX and StartY for Player X
        int startXx = playerXPos.HCell() * UI.CellWidth + UI.CellWidth / 2;
        int startYx = UI.ToolBarHeight + playerXPos.VCell() * UI.CellHeight + UI.CellHeight / 2;

        // Calculate StartX and StartY for Player Y
        int startXy = playerYPos.HCell() * UI.CellWidth + UI.CellWidth / 2;
        int startYy = UI.ToolBarHeight + playerYPos.VCell() * UI.CellHeight + UI.CellHeight / 2;

        // Initialize EndX and EndY for Player X's laser
        int endXx = startXx;
        int endYx = startYx;

        ///////////////////////////////////////////////////////////////////////////////////


        // Determine if playerX can shoot playerY
        bool playerXCanShoot = false;

        switch (playerXDirection) {
        case RIGHT:
            playerXCanShoot = (playerXPos.VCell() == playerYPos.VCell() && playerXPos.HCell() < playerYPos.HCell());
            endXx = startXy; // End horizontally at Player Y's X position
            endYx = startYx; // Same vertical line
            break;
        case LEFT:
            playerXCanShoot = (playerXPos.VCell() == playerYPos.VCell() && playerXPos.HCell() > playerYPos.HCell());
            endXx = startXy; // End horizontally at Player Y's X position
            endYx = startYx; // Same vertical line
            break;
        case UP:
            playerXCanShoot = (playerXPos.HCell() == playerYPos.HCell() && playerXPos.VCell() > playerYPos.VCell());
            endXx = startXx; // Same horizontal line
            endYx = startYy; // End vertically at Player Y's Y position
            break;
        case DOWN:
            playerXCanShoot = (playerXPos.HCell() == playerYPos.HCell() && playerXPos.VCell() < playerYPos.VCell());
            endXx = startXx; // Same horizontal line
            endYx = startYy; // End vertically at Player Y's Y position
            break;
        }


        // Determine if playerY can shoot playerX
        bool playerYCanShoot = false;
        int endXy = startXy;
        int endYy = startYy;

        switch (playerYDirection) {
        case RIGHT:
            playerYCanShoot = (playerYPos.VCell() == playerXPos.VCell() && playerYPos.HCell() < playerXPos.HCell());
            endXy = startXx; // End horizontally at Player X's X position
            endYy = startYy; // Same vertical line
            break;
        case LEFT:
            playerYCanShoot = (playerYPos.VCell() == playerXPos.VCell() && playerYPos.HCell() > playerXPos.HCell());
            endXy = startXx; // End horizontally at Player X's X position
            endYy = startYy; // Same vertical line
            break;
        case UP:
            playerYCanShoot = (playerYPos.HCell() == playerXPos.HCell() && playerYPos.VCell() > playerXPos.VCell());
            endXy = startXy; // Same horizontal line
            endYy = startYx; // End vertically at Player X's Y position
            break;
        case DOWN:
            playerYCanShoot = (playerYPos.HCell() == playerXPos.HCell() && playerYPos.VCell() < playerXPos.VCell());
            endXy = startXy; // Same horizontal line
            endYy = startYx; // End vertically at Player X's Y position
            break;
        }

        if (playerXPos.HCell() == playerYPos.HCell() && playerXPos.VCell() == playerYPos.VCell()) { //Both in the same cell (assume they will shoot eachother)
            playerXCanShoot = true;
            playerYCanShoot = true;
        }

        int playerXDamage = playerX->HasDoubleLaser() ? 2 : 1;
        int playerYDamage = playerY->HasDoubleLaser() ? 2 : 1;


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (playerXCanShoot) {
            //Drawing
            pOut->DrawLaser(startXx, startYx, endXx, endYx);

            if (playerY->HasLaserReflection() && playerX->HasLaserReflection()) {
                // Both players have laser reflection gear
                playerY->DisableLaserReflection();
                playerX->DisableLaserReflection();
                playerY->SetHealth(max(0, playerY->GetHealth() - playerXDamage)); // Player Y takes the damage
                pOut->PrintMessage("Both players have laser reflection gear! Player " + to_string(playerYNumber) + " took the damage after reflections.");
            }


            else if (playerY->HasLaserReflection()) { // Reflect laser
                playerX->SetHealth(max(0, playerX->GetHealth() - playerXDamage));
                playerY->DisableLaserReflection();
                pOut->PrintMessage("Player " + to_string(playerXNumber) + " shot Player " + to_string(playerYNumber) + ", but the damage was reflected back!");
            }
            else if (playerY->HasShield()) {
                playerY->DisableShield(); // Shield used once and then disabled 
                pOut->PrintMessage("Player " + to_string(playerXNumber) + " shot at Player " + to_string(playerYNumber) + ", but the shield protected Player " + to_string(playerYNumber) + "!");
            }
            else {
                playerY->SetHealth(max(0, playerY->GetHealth() - playerXDamage));
                pOut->PrintMessage("Player " + to_string(playerXNumber) + " hit Player " + to_string(playerYNumber) + "! Damage dealt: " + to_string(playerXDamage));
            }
            pIn->GetPointClicked(x, y); // Wait for user to click
            pOut->ClearStatusBar(); // Clear the status bar after click
            //clear Drawing
        }

        if (playerYCanShoot) {
            //Drawing
            pOut->DrawLaser(startXy, startYy, endXy, endYy);

            if (playerX->HasLaserReflection() && playerY->HasLaserReflection()) {
                // Both players have laser reflection gear
                playerX->DisableLaserReflection();
                playerY->DisableLaserReflection();
                playerX->SetHealth(max(0, playerX->GetHealth() - playerYDamage)); // Player X takes the damage
                pOut->PrintMessage("Both players have laser reflection gear! Player " + to_string(playerXNumber) + " took the damage after reflections.");
            }

            else if (playerX->HasLaserReflection()) { // Reflect laser
                playerY->SetHealth(max(0, playerY->GetHealth() - playerYDamage));
                playerX->DisableLaserReflection();
                pOut->PrintMessage("Player " + to_string(playerYNumber) + " shot Player " + to_string(playerXNumber) + ", but the damage was reflected back!");
            }
            else if (playerX->HasShield()) {
                playerX->DisableShield(); // Shield used once and then disabled 
                pOut->PrintMessage("Player " + to_string(playerYNumber) + " shot at Player " + to_string(playerXNumber) + ", but the shield protected Player " + to_string(playerXNumber) + "!");
            }
            else {
                playerX->SetHealth(max(0, playerX->GetHealth() - playerYDamage));
                pOut->PrintMessage("Player " + to_string(playerYNumber) + " hit Player " + to_string(playerXNumber) + "! Damage dealt: " + to_string(playerYDamage));
            }
            pIn->GetPointClicked(x, y); // Wait for user to click
            pOut->ClearStatusBar(); // Clear the status bar after click
            //clear Drawing

        }

        // If neither can shoot
        if (!playerXCanShoot && !playerYCanShoot) {
            pOut->PrintMessage("No players in line of fire. Click to continue.");
            pIn->GetPointClicked(x, y); // Wait for user to click
            pOut->ClearStatusBar(); // Clear the status bar after click
        }

        // Check if the game should end
        if (playerX->GetHealth() == 0) {
            pOut->PrintMessage("Player " + to_string(playerYNumber) + " wins! Game over.");
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();
            pOut->PrintMessage("Start a new Game.");
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();
            pGrid->SetEndGame(true);
            return;
        }

        if (playerY->GetHealth() == 0) {
            pOut->PrintMessage("Player " + to_string(playerXNumber) + " wins! Game over.");
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();
            pOut->PrintMessage("Start a new Game.");
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();
            pGrid->SetEndGame(true);
            return;
        }


        pGrid->AdvanceCurrentPlayer();
        pOut->ClearStatusBar();

        pOut->ClearGridArea();
        pGrid->UpdateInterface();
    }
}
