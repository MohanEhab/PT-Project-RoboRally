#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Belt.h"
#include "Player.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed

{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

bool Grid::IsCellEmpty(const CellPosition& pos) const
{
	GameObject* pObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject(); //pObject should store the object if there is (copied it from the syntax/idea function above)
	return (pObject == nullptr); // Return true if the cell contains no object
}


// Note: You may need to change the return type of this function (Think)========DONE
bool Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
		return true;
	}
	return false;
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's triangle from the old cell position
	player->ClearDrawing(pOut);
	
	
	for (int i = 0; i < MaxPlayerCount; i++) { //fix issue of player being removed if another player passed by it
		Player* otherPlayer = PlayerList[i];
		if (otherPlayer != player &&
			otherPlayer->GetCell()->GetCellPosition().VCell() == player->GetCell()->GetCellPosition().VCell() &&
			otherPlayer->GetCell()->GetCellPosition().HCell() == player->GetCell()->GetCellPosition().HCell()) {
			// Redraw the other player after clearing
			otherPlayer->Draw(pOut);
		}
	}
	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	//fixes issue of player delete belts drawn 
	for (int i = 0; i < NumVerticalCells; ++i) {
		for (int j = 0; j < NumHorizontalCells; ++j) {
			Cell* cell = CellList[i][j];
			Belt* belt = cell->HasBelt(); 
			if (belt) {
				CellPosition beltStart = belt->GetPosition();
				CellPosition beltEnd = belt->GetEndPosition();

					pOut->DrawBelt(beltStart, beltEnd);
				}
			}
		}



	// Draw the player's triangle on the new cell position
	player->Draw(pOut);

}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(GameObject * gameObject) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = gameObject;
}

GameObject * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Belt * Grid::GetNextBelt(const CellPosition & position)
{	

	int startH = position.HCell(); // represents the start hCell in the current row to search for the belt in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			Cell* cell = CellList[i][j]; // Get the cell at (i, j)
			if ( cell->HasBelt()) // Check if the cell contains a belt
			{
				return cell->HasBelt(); // Return the belt
			}

			///TODO: Check if CellList[i][j] has a belt, if yes return it
			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Cell* Grid::GetStartingCell() const
{
	return CellList[NumVerticalCells - 1][0];
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without waterpits or dangerzone 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrWaterPitOrDangerZone(pOut);
			}
		}

		// 2- Draw other game objects(excluding waterpit and dangerzone)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawGameObject(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = P " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cgame objects do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


bool Grid::HasFlag() const
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			// Check if the cell contains a flag
			if (CellList[i][j]->HasFlag())
			{
				return true; // A flag exists
			}
		}
	}
	return false; // No flag found
}

bool Grid::HasAntenna() const
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			// Check if the cell contains an Antenna
			if (CellList[i][j]->HasAntenna())
			{
				return true; // An Antenna exists
			}
		}
	}
	return false; // No Antenna found
}
CellPosition Grid::FindAntennaPosition() const
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasAntenna()) {
				return CellList[i][j]->GetCellPosition();
			}
		}
	}
	return CellPosition(-1, -1); // Return invalid position if no antenna is found
}

void Grid::ExecutePlayerCommands(const Command commands[], int numCommands)
{
	Player* currPlayer = GetCurrentPlayer(); // * to get curr player 
	Command tempCommands[5];
	for (int i = 0; i < numCommands; i++)
	{
		tempCommands[i] = commands[i];
	}

	UpdateInterface(); //update after executing commands
}

void Grid::ResetAllPlayers()
{
	for (int i = 0; i < MaxPlayerCount; i++) {
		if (PlayerList[i] != nullptr) {
			PlayerList[i]->ClearDrawing(pOut); // Remove the player's graphical representation
			delete PlayerList[i]; // Free memory
			PlayerList[i] = NULL; // Avoid dangling reference
		}
	}

	// Reinitialize players
	Cell* start = GetStartingCell();
	for (int i = 0; i < MaxPlayerCount; i++) {
		PlayerList[i] = new Player(start, i); // Create new players
		PlayerList[i]->Draw(pOut); // Draw players on the grid
	}

	currPlayerNumber = 0; // Reset current player to the first player
}

void Grid::DisPlayerInfo() const
{
	const char* DirectionString[] = { "UP","DOWN","RIGHT","LEFT" };
	//static arr to get the dir as a string
	string playersInfo = "";
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		Player* player = PlayerList[i];
		playersInfo = playersInfo + "P" + to_string(player->GetPlayerNumber()+1);
		playersInfo += "(" + to_string(player->GetCell()->GetCellPosition().GetCellNum()) + ",";
		playersInfo += DirectionString[player->GetDirection()];
		playersInfo += ", " + to_string(player->GetHealth()) + ")";

		if (i < MaxPlayerCount - 1)
			playersInfo = playersInfo + ",";
	}
	playersInfo = playersInfo + "| Curr P = " + to_string(currPlayerNumber+1);
	pOut->PrintPlayersInfo(playersInfo);
}

void Grid::ClearAllObjects()
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			Cell* cell = CellList[i][j];
			if (cell->GetGameObject())
			{
				cell->SetGameObject(NULL); //removes object if found
			}
		}
	}
}
Cell* Grid::GetCell(const CellPosition& pos) const
{
	return CellList[pos.VCell()][pos.HCell()]; // Return the corresponding cell
}



Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}