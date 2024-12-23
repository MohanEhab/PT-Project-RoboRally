#include "ShootingAction.h"

ShootingAction::ShootingAction(ApplicationManager* pApp):Action(pApp)
{}

ShootingAction::~ShootingAction()
{}

void ShootingAction::ReadActionParameters()
{}

void ShootingAction::Execute() {
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;

    Player* player1 = pGrid->GetCurrentPlayer();
    pGrid->AdvanceCurrentPlayer()
    Player* player2 = pGrid->GetCurrentPlayer();

    // Get positions and directions of both players
    CellPosition player1Pos = player1->GetCell()->GetCellPosition();
    CellPosition player2Pos = player2->GetCell()->GetCellPosition();

    Direction player1Direction = player1->GetDirection();
    Direction player2Direction = player2->GetDirection();

    // Check if players are in the same cell
    if (player1Pos.HCell() == player2Pos.HCell() && player1Pos.VCell() == player2Pos.VCell()) {
        int player1Damage = player1->HasDoubleLaser() ? 2 : 1;
        int player2Damage = player2->HasDoubleLaser() ? 2 : 1;

        player1->SetHealth(player1->GetHealth() - player2Damage);
        player2->SetHealth(player2->GetHealth() - player1Damage);

        pOut->PrintMessage("Players are in the same cell! They shoot each other. Damage exchanged.");
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
        return;
    }

    // Determine if player1 can shoot player2
    bool player1CanShoot = false;
    switch (player1Direction) {
    case RIGHT:
        player1CanShoot = (player1Pos.VCell() == player2Pos.VCell() && player1Pos.HCell() < player2Pos.HCell());
        break;
    case LEFT:
        player1CanShoot = (player1Pos.VCell() == player2Pos.VCell() && player1Pos.HCell() > player2Pos.HCell());
        break;
    case UP:
        player1CanShoot = (player1Pos.HCell() == player2Pos.HCell() && player1Pos.VCell() > player2Pos.VCell());
        break;
    case DOWN:
        player1CanShoot = (player1Pos.HCell() == player2Pos.HCell() && player1Pos.VCell() < player2Pos.VCell());
        break;
    }

    // Determine if player2 can shoot player1
    bool player2CanShoot = false;
    switch (player2Direction) {
    case RIGHT:
        player2CanShoot = (player2Pos.VCell() == player1Pos.VCell() && player2Pos.HCell() < player1Pos.HCell());
        break;
    case LEFT:
        player2CanShoot = (player2Pos.VCell() == player1Pos.VCell() && player2Pos.HCell() > player1Pos.HCell());
        break;
    case UP:
        player2CanShoot = (player2Pos.HCell() == player1Pos.HCell() && player2Pos.VCell() > player1Pos.VCell());
        break;
    case DOWN:
        player2CanShoot = (player2Pos.HCell() == player1Pos.HCell() && player2Pos.VCell() < player1Pos.VCell());
        break;
    }



    int player1Damage = player1->HasDoubleLaser() ? 2 : 1; //created both possible damages to be able to use them easily down
    int player2Damage = player2->HasDoubleLaser() ? 2 : 1;


    if (player1CanShoot) {
        if (player2->HasLaserReflection()) { // Reflect laser
            player1->SetHealth(player1->GetHealth() - player1Damage);
            player2->DisableLaserReflection();
            pOut->PrintMessage("Player 1 shot Player 2, but the damage was reflected back!");
        }
        else if (player2->HasShield()) {
            player2->DisableShield(); // Shield used once and then disabled 
            pOut->PrintMessage("Player 1 shot at Player 2, but the shield protected Player 2!");
        }
        else {
            int newHealth = player2->GetHealth() - player1Damage;
            player2->SetHealth(newHealth);
            pOut->PrintMessage("Player 1 hit Player 2! Damage dealt: " + to_string(player1Damage));
        }
        pIn->GetPointClicked(x, y); // Wait for user to click
        pOut->ClearStatusBar(); // Clear the status bar after click
    }

    if (player2CanShoot) {
        if (player1->HasLaserReflection()) { // Reflect laser
            player2->SetHealth(player2->GetHealth() - player2Damage);
            player1->DisableLaserReflection();
            pOut->PrintMessage("Player 2 shot Player 1, but the damage was reflected back!");
        }
        else if (player1->HasShield()) {
            player1->DisableShield(); // Shield used once and then disabled 
            pOut->PrintMessage("Player 2 shot at Player 1, but the shield protected Player 1!");
        }
        else {
            int newHealth = player1->GetHealth() - player2Damage;
            player1->SetHealth(newHealth);
            pOut->PrintMessage("Player 2 hit Player 1! Damage dealt: " + to_string(player2Damage));
        }
        pIn->GetPointClicked(x, y); // Wait for user to click
        pOut->ClearStatusBar(); // Clear the status bar after click
    }


    // If neither can shoot
    if (!player1CanShoot && !player2CanShoot) {
        pOut->PrintMessage("No players in line of fire. Click to continue.");
        pIn->GetPointClicked(x, y); // Wait for user to click
        pOut->ClearStatusBar(); // Clear the status bar after click
    }

    pOut->ClearStatusBar();
}

