#include "DangerZone.h"



DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}

void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}

void DangerZone::Apply(Grid * pGrid, Player * pPlayer)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a danger zone. Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	pOut->PrintMessage("You have reached a danger zone. Click to continue...");
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	// 2- Apply the danger zone's effect by reducing the health of the player by 1 
	if (pPlayer->HasShield()) {
		pPlayer->DisableShield(); // Break the shield
		pOut->PrintMessage("Your shield protected you from the danger zone, but it is now broken. Click to continue...");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	else {
		// 3- Apply the danger zone's effect by reducing the health of the player by 1 
		int currentHealth = pPlayer->GetHealth();
		pPlayer->SetHealth(currentHealth - 1);
		pOut->PrintMessage("You lost 1 health in the danger zone. Click to continue...");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}

	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	pGrid->UpdateInterface();
}


DangerZone::~DangerZone()
{
}
