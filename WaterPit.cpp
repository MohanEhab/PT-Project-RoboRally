#include "WaterPit.h"



WaterPit::WaterPit(const CellPosition & waterPitPosition):GameObject(waterPitPosition)
{
}

void WaterPit::Draw(Output * pOut) const
{
	pOut->DrawWaterPit(position);
}

void WaterPit::Apply(Grid * pGrid, Player * pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message, make sure to edit this message according to which player wins "You drowned in a water pit. Player (0/1) wins !  Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	
	// 2- Apply the water pit's effect by setting the player's health which drowned to zero and ending the game
	pPlayer->SetHealth(0);
	int drownedPlayer = pPlayer->GetPlayerNumber();
	int winningPlayer{0};
	if (drownedPlayer == 0)
		winningPlayer = 1;
	
	pOut->PrintMessage("You drowned in a water pit. Player " +to_string(winningPlayer) + " wins! Click to continue...");
	pIn->GetPointClicked(x, y);
	pGrid->SetEndGame(true);


	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	pGrid->UpdateInterface(); 
}


WaterPit::~WaterPit()
{
}
