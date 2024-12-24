#include "Grid.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Cell.h"
#include "GameObject.h"
#include "Belt.h"
#include "Player.h"
#include"Flag.h"
#include "cell.h"
#include "Antenna.h"
#include "WaterPit.h"
#include "Workshop.h"
#include "RotatingGear.h"
#include "DangerZone.h"
#include"CopyObjectAction.h"
#include "Player.h"
#include "CellPosition.h"
using namespace std;


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


GameObject* Grid::GetObjectFromCell(const CellPosition& pos) const
{
	if (pos.IsValidCell()) { // Check if the position is valid
		Cell* pCell = CellList[pos.VCell()][pos.HCell()]; // Get the cell at the specified position
		if (pCell) {
			return pCell->GetGameObject(); // Return the GameObject in the cell
		}
	}
	return nullptr; // Return nullptr if the position is invalid or the cell is empty
}
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
int Grid::CountGameObjects(int Type) const
{
	int count = 0;
	for (int i = 0; i < NumVerticalCells; i++) {
		for (int j = 0; j < NumHorizontalCells; j++) {
			Cell* pCell = CellList[i][j];
			if (pCell && pCell->GetGameObject() && pCell->GetGameObject()->GetType() == Type) {
				count++;
			}
		}
	}
	return count;
}
void Grid::ClearGrid()
{
	for (int i = 0; i < NumVerticalCells; i++) { // loops iterate thruogh each row
		for (int j = 0; j < NumHorizontalCells; j++) {// inside each row we iteraee through each cloumn
			Cell* pCell = CellList[i][j];
			if (pCell) {// checks if its valid
				GameObject* pObj = pCell->GetGameObject();
				if (pObj) {//checks if there is a gameobject in the cell
					delete pObj; // if gameobejct exsits we delete it to free up memory
					pCell->SetGameObject(nullptr); //cell is set to nullptr which indicates cell no longer contains object 
				}
			}
		}
	}
}
CellPosition Grid::GetPositionFromCellNum(int cellNum)
{
	return CellPosition::GetCellPositionFromNum(cellNum);
}
void Grid::LoadAll(ifstream& InFile) {
	int count;

	// 1. Load Flags
	InFile >> count; // Read the number of flags
	for (int i = 0; i < count; i++) {
		Flag* flag = new Flag(); // Use default constructor
		flag->Load(InFile);      // Load data from the file
		AddObjectToCell(flag);   // Add object to the cell
	}

	// 2. Load Water Pits
	InFile >> count; // Read the number of water pits
	for (int i = 0; i < count; i++) {
		WaterPit* waterPit = new WaterPit(); // Use default constructor
		waterPit->Load(InFile);             // Load data from the file
		AddObjectToCell(waterPit);          // Add object to the cell
	}

	// 3. Load Danger Zones
	InFile >> count; // Read the number of danger zones
	for (int i = 0; i < count; i++) {
		DangerZone* dangerZone = new DangerZone(); // Use default constructor
		dangerZone->Load(InFile);                 // Load data from the file
		AddObjectToCell(dangerZone);              // Add object to the cell
	}

	// 4. Load Belts
	InFile >> count; // Read the number of belts
	for (int i = 0; i < count; i++) {
		Belt* belt = new Belt(); // Use default constructor
		belt->Load(InFile);      // Load data from the file
		AddObjectToCell(belt);   // Add object to the cell
	}

	// 5. Load Workshops
	InFile >> count; // Read the number of workshops
	for (int i = 0; i < count; i++) {
		Workshop* workshop = new Workshop(); // Use default constructor
		workshop->Load(InFile);              // Load data from the file
		AddObjectToCell(workshop);           // Add object to the cell
	}

	// 6. Load Antennas
	InFile >> count; // Read the number of antennas
	for (int i = 0; i < count; i++) {
		Antenna* antenna = new Antenna(); // Use default constructor
		antenna->Load(InFile);            // Load data from the file
		AddObjectToCell(antenna);         // Add object to the cell
	}

	// 7. Load Rotating Gears
	InFile >> count; // Read the number of rotating gears
	for (int i = 0; i < count; i++) {
		RotatingGear* rotatingGear = new RotatingGear(); // Use default constructor
		rotatingGear->Load(InFile);                     // Load data from the file
		AddObjectToCell(rotatingGear);                  // Add object to the cell
	}

	// Update the interface to reflect the loaded objects
	UpdateInterface();

	// Display a success message
	Output* pOut = GetOutput();
	pOut->PrintMessage("Grid loaded successfully!");
}void Grid::SaveAll(ofstream& OutFile, int Type) {
	int count = CountGameObjects(Type);
	OutFile << count << endl; // Write the count first
	for (int i = 0; i < NumVerticalCells; i++) {
		for (int j = 0; j < NumHorizontalCells; j++) {
			Cell* pCell = CellList[i][j]; // Get the cell
			if (pCell) {
				GameObject* pObj = pCell->GetGameObject();
				if (pObj) {
					pObj->Save(OutFile, Type); // Call the GameObject's Save method
				}
			}
		}
	}
}
// Note: You may need to change the return type of this function (Think)========DONE
GameObject* Grid::RemoveObjectFromCell(const CellPosition& pos) {
	if (!pos.IsValidCell()) {
		return nullptr;
	}

	Cell* pCell = CellList[pos.VCell()][pos.HCell()];
	if (!pCell) {
		return nullptr;
	}

	GameObject* pObj = pCell->GetGameObject();
	if (pObj) {
		pCell->SetGameObject(nullptr);
	}

	return pObj;
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	// Clear the player's triangle from the old cell position
	player->ClearDrawing(pOut);
	// Set the player's CELL with the new position
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);
	// Draw the player's triangle on the new cell position
	player->Draw(pOut);
	this->UpdateInterface();

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
		for (int i = NumVerticalCells - 1; i >= 0; i--) {
			for (int j = 0; j < NumHorizontalCells; j++) {
				CellList[i][j]->DrawCellOrWaterPitOrDangerZone(pOut);
			}
		}
		for (int i = NumVerticalCells - 1; i >= 0; i--) {
			for (int j = 0; j < NumHorizontalCells; j++) {
				CellList[i][j]->DrawGameObject(pOut);
			}
		}
		for (int i = 0; i < MaxPlayerCount; i++) {
			PlayerList[i]->Draw(pOut);
		}
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