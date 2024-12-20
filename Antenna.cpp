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
	pGrid->PrintErrorMessage("The antenna will decide the turn of players. Click to continue ...");
	pGrid->GetInput()->GetPointClicked(x, y);

	// 2- Apply the antenna effect by following these notes, check grid class and decide which function to use
	if (!pGrid->HasAntenna()) {
		pGrid->PrintErrorMessage("Error: No antenna exists on the grid. Click to continue...");
		return;
	}
	if (pGrid->GetEndGame()) {
		pGrid->PrintErrorMessage("The game is already marked as ended. Click to continue...");
		return;
	}
    struct PlayerInfo {
        Player* player;
        int distance;
    };

    PlayerInfo playerInfos[MaxPlayerCount];

    for (int i = 0; i < MaxPlayerCount; i++) {
        playerInfos[i].player = pGrid->GetPlayer(i); 
        Cell* playerCell = playerInfos[i].player->GetCell();
        CellPosition playerPos = playerCell->GetCellPosition();
        CellPosition antennaPos = this->GetPosition(); 

       
        int vDistance = (playerPos.VCell() > antennaPos.VCell())
            ? (playerPos.VCell() - antennaPos.VCell())
            : (antennaPos.VCell() - playerPos.VCell());
        int hDistance = (playerPos.HCell() > antennaPos.HCell())
            ? (playerPos.HCell() - antennaPos.HCell())
            : (antennaPos.HCell() - playerPos.HCell());

        playerInfos[i].distance = vDistance + hDistance;
    }
    std::sort(playerInfos, playerInfos + MaxPlayerCount, [](const PlayerInfo& a, const PlayerInfo& b) {
        if (a.distance == b.distance)
            return a.player->GetPlayerNumber() < b.player->GetPlayerNumber(); 
        return a.distance < b.distance;
        });

    
    for (int i = 0; i < MaxPlayerCount; i++) {
        if (playerInfos[i].player->GetHealth() <= 0) {
            pGrid->PrintErrorMessage("Error: Player " + std::to_string(playerInfos[i].player->GetPlayerNumber()) + " is eliminated. Skipping...");
            continue;
        }
    }
    for (int i = 0; i < MaxPlayerCount; i++) {
        pGrid->SetPlayerTurnOrder(i, playerInfos[i].player->GetPlayerNumber());
    }
    // 3- After deciding the turn of player Print a message indicating which player will play first example: "Player 1 will play first"

    pGrid->AdvanceCurrentPlayer();
    pGrid->PrintErrorMessage("Player " + std::to_string(playerInfos[0].player->GetPlayerNumber()) + " will play first.");
}

	
}


Antenna::~Antenna()
{
}
