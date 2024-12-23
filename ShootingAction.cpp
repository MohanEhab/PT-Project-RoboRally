#include "ShootingAction.h"

ShootingAction::ShootingAction(ApplicationManager* pApp) :Action(pApp)
{
}

ShootingAction::~ShootingAction()
{
}


void ShootingAction::Execute() {
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;

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


    // Determine if playerX can shoot playerY
    bool playerXCanShoot = false;
    switch (playerXDirection) {
    case RIGHT:
        playerXCanShoot = (playerXPos.VCell() == playerYPos.VCell() && playerXPos.HCell() < playerYPos.HCell());
        break;
    case LEFT:
        playerXCanShoot = (playerXPos.VCell() == playerYPos.VCell() && playerXPos.HCell() > playerYPos.HCell());
        break;
    case UP:
        playerXCanShoot = (playerXPos.HCell() == playerYPos.HCell() && playerXPos.VCell() > playerYPos.VCell());
        break;
    case DOWN:
        playerXCanShoot = (playerXPos.HCell() == playerYPos.HCell() && playerXPos.VCell() < playerYPos.VCell());
        break;
    }

    // Determine if playerY can shoot playerX
    bool playerYCanShoot = false;
    switch (playerYDirection) {
    case RIGHT:
        playerYCanShoot = (playerYPos.VCell() == playerXPos.VCell() && playerYPos.HCell() < playerXPos.HCell());
        break;
    case LEFT:
        playerYCanShoot = (playerYPos.VCell() == playerXPos.VCell() && playerYPos.HCell() > playerXPos.HCell());
        break;
    case UP:
        playerYCanShoot = (playerYPos.HCell() == playerXPos.HCell() && playerYPos.VCell() > playerXPos.VCell());
        break;
    case DOWN:
        playerYCanShoot = (playerYPos.HCell() == playerXPos.HCell() && playerYPos.VCell() < playerXPos.VCell());
        break;
    }

    if (playerXPos.HCell() == playerYPos.HCell() && playerXPos.VCell() == playerYPos.VCell()) { //Both in the same cell (assume they will shoot eachother)
        playerXCanShoot = true;
        playerYCanShoot = true;
    }

    int playerXDamage = playerX->HasDoubleLaser() ? 2 : 1;
    int playerYDamage = playerY->HasDoubleLaser() ? 2 : 1;

    if (playerXCanShoot) {
        //Drawing
      
        
        if (playerY->HasLaserReflection() && playerX->HasLaserReflection()) {
            // Both players have laser reflection gear
            playerY->DisableLaserReflection();
            playerX->DisableLaserReflection();
            playerY->SetHealth(playerY->GetHealth() - playerXDamage); // Player Y takes the damage
            pOut->PrintMessage("Both players have laser reflection gear! Player " + to_string(playerYNumber) + " took the damage after reflections.");
        }
        
        
        else if (playerY->HasLaserReflection()) { // Reflect laser
            playerX->SetHealth(playerX->GetHealth() - playerXDamage);
            playerY->DisableLaserReflection();
            pOut->PrintMessage("Player " + to_string(playerXNumber) + " shot Player " + to_string(playerYNumber) + ", but the damage was reflected back!");
        }
        else if (playerY->HasShield()) {
            playerY->DisableShield(); // Shield used once and then disabled 
            pOut->PrintMessage("Player " + to_string(playerXNumber) + " shot at Player " + to_string(playerYNumber) + ", but the shield protected Player " + to_string(playerYNumber) + "!");
        }
        else {
            playerY->SetHealth(playerY->GetHealth() - playerXDamage);
            pOut->PrintMessage("Player " + to_string(playerXNumber) + " hit Player " + to_string(playerYNumber) + "! Damage dealt: " + to_string(playerXDamage));
        }
        pIn->GetPointClicked(x, y); // Wait for user to click
        pOut->ClearStatusBar(); // Clear the status bar after click

    }

    if (playerYCanShoot) {
        //Drawing
        
        if (playerX->HasLaserReflection() && playerY->HasLaserReflection()) {
            // Both players have laser reflection gear
            playerX->DisableLaserReflection();
            playerY->DisableLaserReflection();
            playerX->SetHealth(playerX->GetHealth() - playerYDamage); // Player X takes the damage
            pOut->PrintMessage("Both players have laser reflection gear! Player " + to_string(playerXNumber) + " took the damage after reflections.");
        }
    
        else if (playerX->HasLaserReflection()) { // Reflect laser
            playerY->SetHealth(playerY->GetHealth() - playerYDamage);
            playerX->DisableLaserReflection();
            pOut->PrintMessage("Player " + to_string(playerYNumber) + " shot Player " + to_string(playerXNumber) + ", but the damage was reflected back!");
        }
        else if (playerX->HasShield()) {
            playerX->DisableShield(); // Shield used once and then disabled 
            pOut->PrintMessage("Player " + to_string(playerYNumber) + " shot at Player " + to_string(playerXNumber) + ", but the shield protected Player " + to_string(playerXNumber) + "!");
        }
        else {
            playerX->SetHealth(playerX->GetHealth() - playerYDamage);
            pOut->PrintMessage("Player " + to_string(playerYNumber) + " hit Player " + to_string(playerXNumber) + "! Damage dealt: " + to_string(playerYDamage));
        }
        pIn->GetPointClicked(x, y); // Wait for user to click
        pOut->ClearStatusBar(); // Clear the status bar after click

    }

    // If neither can shoot
    if (!playerXCanShoot && !playerYCanShoot) {
        pOut->PrintMessage("No players in line of fire. Click to continue.");
        pIn->GetPointClicked(x, y); // Wait for user to click
        pOut->ClearStatusBar(); // Clear the status bar after click
    }
    pGrid->AdvanceCurrentPlayer();
    pOut->ClearStatusBar();
}
