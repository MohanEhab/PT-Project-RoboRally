#include "DangerZone.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;




DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}
DangerZone::DangerZone() : GameObject(CellPosition()) {
	// Initialize with default CellPosition
}
void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}
GameObject* DangerZone::Copy() const
{
	return new DangerZone(*this); // Return a new DangerZone object using the copy constructor
}
void DangerZone::Save(ofstream& OutFile, int Type)
{
	if (Type == GetType()) { //  3 represents DangerZones is thired saved 
		OutFile << position.GetCellNum() << endl;
	}
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
		pPlayer->SetHealth(max(0,currentHealth - 1));

		if (pPlayer->GetHealth() == 0) {
			pOut ->PrintMessage("Player " + to_string(pPlayer->GetPlayerNumber()) + " Has fallen and died in danger zone. Clcik to continue..");
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			pGrid->AdvanceCurrentPlayer();
			pOut->PrintMessage("Player " + to_string(pPlayer->GetPlayerNumber()) + " Has won! Clcik to continue..");
			pGrid->SetEndGame(true);
		}
		else {
			pOut->PrintMessage("You lost 1 health in the danger zone. Click to continue...");
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
		}
		
	}

	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	pGrid->UpdateInterface();
}
void DangerZone::Load(ifstream& InFile)
{
	int cellNum;
	InFile >> cellNum;
	position = CellPosition::GetCellPositionFromNum(cellNum);
}

int DangerZone::GetType() const
{
	return 3;
}


DangerZone::~DangerZone()
{
}
