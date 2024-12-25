#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell * pCell;		   // pointer to the current Cell of the player

	const int playerNum ;   // the player number (from 0 to MaxPlayerCount-1)
	                       // player number does NOT change after construction (const.)

	
	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	Direction currDirection; // Current Direction of the player
	int health;				// Player's current health points
	
	LaserType equippedLaser; // Player's equipped laser type (laser or double laser)

	bool hasDoubleLaser;      // Tracks if the player owns a double laser
	bool hasExtendedMemory;   // Tracks if the player owns extended memory
	bool hasToolkit;          // Tracks if the player owns a toolkit
	bool hasHackDevice;       // Tracks if the player owns a hack device
	bool hasShield;           //Tracks if the player has a shield (bonus)
	bool hasLaserReflection;  //Tracks if the player has a Laser Reflection Gear (bonus)
	bool isRebootnRepair;	          //Tracks if player chose to reboot and repair

	// owned equipments
	// carried consumables
	// carried laser type (default, double laser)
	// isHacked (to indicate whether the player is blocked to play the round, as a result of the opponent using a hacking device)
	bool isActive;
	Command savedCommands[6];
	Command availableCommands[10];
	int savedCommandCount;
	int availableCommandCount;
public:

	Player(Cell * pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetHealth(int h);			// A setter for the health points
	int GetHealth();				// A getter for the health points
	int GetPlayerNumber() const; 
	
	Direction GetDirection() const;
	void RebootAndRepair(Grid* pGrid);
	void RotateClockwise(Grid* pGrid);
	void RotateCounterClockwise(Grid* pGrid);
	string GetPlayerInfo() const;

	bool HasShield() const;
	void DisableShield();
	void EnableShield();
	
	bool HasLaserReflection() const;
	void DisableLaserReflection();
	void EnableLaserReflection();
	
	bool HasRebootnRepair();
	void setRebootnRepair(bool n);

	///TODO: You can add setters and getters for data members here (if needed)

	// ====== Drawing Functions ======
	void setInactive();
	void setActive();
	bool isCurrentlyActive() const;
	void UseToolkit(Grid* pGrid);
	void UseHackDevice(Grid* pGrid);
	void resetForNextRound();
	
	void Draw(Output* pOut) const;			// Draws the Player's Triangle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Triangle from its current cell
	void SelectCommands(Grid* pGrid, Command availableCommands[]);
	Command* GetSavedCommands();
	int GetSavedCommandCount() const;
	void SaveCommands(const Command commands[], int count);
	string CommandToString(Command cmd) const;
	void DisplayRandomCommands(Grid* pGrid, Command availableCommands[]);
	int GetAvailableCommandCount()const; 
	Command* GetAvailableCommands(); 

	// ====== Equipment Functions ======
	void EquipDoubleLaser();             // Equip the player with a double laser
	bool NeedsRebootAndRepair() const;
	bool HasDoubleLaser() const;         // Check if the player has a double laser

	void EnableExtendedMemory();         // Enable extended memory
	bool HasExtendedMemory() const;      // Check if the player has extended memory
	void disableExtendedMemory();
	void AddToolkit();                   // Add a toolkit to the player
	bool HasToolkit() const;             // Check if the player has a toolkit

	void AddHackDevice();                // Add a hack device to the player
	bool HasHackDevice() const;          // Check if the player has a hack device
	void EquipLaser(LaserType laser);    //Equips player laser type
	// ====== Game Functions ======

	void Move(Grid * pGrid, Command moveCommands[]);	// Moves the Player with the passed move command
														// and Applies the Game Object's effect (if any) of the end reached cell 
														// for example, if the end cell contains a belt, take it
	
	void AppendPlayerInfo(string & playersInfo) const; // Appends player's info to the input string, 
	                                                   // for example: P0(Direction, health)

};

