#include "Antenna.h"




Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid * pGrid, Player * pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;
    pOut->PrintMessage("the antenna will decide the turn of players. Click to continue ...");
    pIn->GetPointClicked(x, y); // Wait for the user to click
    pOut->ClearStatusBar();
	// 2- Apply the antenna effect by following these notes, check grid class and decide which function to use
	if (!pGrid->HasAntenna()) {
		pGrid->PrintErrorMessage("Error: No antenna exists on the grid. Click to continue...");
		return;
	}
	if (pGrid->GetEndGame()) {
		pGrid->PrintErrorMessage("The game is already marked as ended. Click to continue...");
		return;
	}
    int distances[MaxPlayerCount];

    // 4. Calculate distance for each player
    for (int i = 0; i < MaxPlayerCount; i++) {
        Player* player = pGrid->PlayerList[i]; // Direct access to PlayerList
        CellPosition playerPos = player->GetCell()->GetCellPosition();
        CellPosition antennaPos = this->GetPosition();

        int vDistance = playerPos.VCell() > antennaPos.VCell()
            ? playerPos.VCell() - antennaPos.VCell()
            : antennaPos.VCell() - playerPos.VCell();
        int hDistance = playerPos.HCell() > antennaPos.HCell()
            ? playerPos.HCell() - antennaPos.HCell()
            : antennaPos.HCell() - playerPos.HCell();

        distances[i] = vDistance + hDistance;
    }

    // Sort players in PlayerList based on distances
    for (int i = 0; i < MaxPlayerCount - 1; i++) {
        for (int j = i + 1; j < MaxPlayerCount; j++) {
            if (distances[j] < distances[i] ||
                (distances[j] == distances[i] && pGrid->PlayerList[j]->GetPlayerNumber() < pGrid->PlayerList[i]->GetPlayerNumber())) {
                // Swap players and distances
                std::swap(pGrid->PlayerList[i], pGrid->PlayerList[j]);
                std::swap(distances[i], distances[j]);
            }
        }
    }
    pGrid->AdvanceCurrentPlayer();
    pGrid->PrintErrorMessage("Player " + std::to_string(pGrid->PlayerList[0]->GetPlayerNumber()) + " will play first.");

    


	Antenna::~Antenna()
	{
	}
