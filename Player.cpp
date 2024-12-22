#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), health(10), playerNum(playerNum), currDirection(RIGHT),hasDoubleLaser(false),hasExtendedMemory(false), hasToolkit(false),hasHackDevice(false), equippedLaser(BASIC_LASER)
{
	this->pCell = pCell;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetHealth(int h)
{
	// Ensure health is not negative
	if (h < 0 || h >10)
		this->health = 0;
	else
		this->health = h;
	
	///TODO: Do any needed validations
}

int Player::GetHealth()
{
	return this->health;
}

// ====== Equipment Functions ======

void Player::EquipLaser(LaserType laser) {
	equippedLaser = laser;
}

void Player::EquipDoubleLaser() {
	
	EquipLaser(DOUBLE_LASER);
	hasDoubleLaser = true;
}

bool Player::HasDoubleLaser() const {
	return hasDoubleLaser;
}

void Player::EnableExtendedMemory() {
	
	//code TODO()
	hasExtendedMemory = true;
}

bool Player::HasExtendedMemory() const {
	return hasExtendedMemory;
}

void Player::AddToolkit() {
	
	//code TODO()
	hasToolkit = true;
}

bool Player::HasToolkit() const {
	return hasToolkit;
}

void Player::AddHackDevice() {
	
	//code TODO()
	hasHackDevice = true;
}

bool Player::HasHackDevice() const {
	return hasHackDevice;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	if (pCell != nullptr)
		pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor, currDirection);
	


	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	///TODO: Modify the cellColor to draw the correct cellColor (hint: if cell contains non-default cellColor)
	color cellColor = UI.CellColor;
	
	pOut->DrawCell(pCell->GetCellPosition(), cellColor);
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, Command moveCommands[])
{
	int x, y;
	const int maxCommands = 5;
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	for (int i = 0; i < maxCommands; i++)
	{
		if (moveCommands[i] == NO_COMMAND)
		{
			break;
		}
		CellPosition currentPos = pCell->GetCellPosition();
		CellPosition newPos = currentPos;
		switch (moveCommands[i])
		{
		case MOVE_FORWARD_ONE_STEP:
			// Move forward based on the player's direction
			switch (currDirection) {
			case UP:
				newPos.SetVCell(newPos.VCell() - 1); // Move up
				break;
			case DOWN:
				newPos.SetVCell(newPos.VCell() + 1); // Move down
				break;
			case LEFT:
				newPos.SetHCell(newPos.HCell() - 1); // Move left
				break;
			case RIGHT:
				newPos.SetHCell(newPos.HCell() + 1); // Move right
				break;
			}
			break;
		case MOVE_FORWARD_TWO_STEPS:
			switch (currDirection) {
			case UP:
				newPos.SetVCell(newPos.VCell() - 2); // Move up 2 steps
				break;
			case DOWN:
				newPos.SetVCell(newPos.VCell() + 2); // Move down 2 steps
				break;
			case LEFT:
				newPos.SetHCell(newPos.HCell() - 2); // Move left 2 steps
				break;
			case RIGHT:
				newPos.SetHCell(newPos.HCell() + 2); // Move right 2 steps
				break;
			}
			break;
		case MOVE_FORWARD_THREE_STEPS:
			switch (currDirection) {
			case UP:
				newPos.SetVCell(currentPos.VCell() - 3);
				break;
			case DOWN:
				newPos.SetVCell(currentPos.VCell() + 3);
				break;
			case LEFT:
				newPos.SetHCell(currentPos.HCell() - 3);
				break;
			case RIGHT:
				newPos.SetHCell(currentPos.HCell() + 3);
				break;
			}
			break;

		case MOVE_BACKWARD_ONE_STEP:
			switch (currDirection) {
			case UP:
				newPos.SetVCell(currentPos.VCell() + 1);
				break;
			case DOWN:
				newPos.SetVCell(currentPos.VCell() - 1);
				break;
			case LEFT:
				newPos.SetHCell(currentPos.HCell() + 1);
				break;
			case RIGHT:
				newPos.SetHCell(currentPos.HCell() - 1);
				break;
			}
			break;

		case MOVE_BACKWARD_TWO_STEPS:
			switch (currDirection) {
			case UP:
				newPos.SetVCell(currentPos.VCell() + 2);
				break;
			case DOWN:
				newPos.SetVCell(currentPos.VCell() - 2);
				break;
			case LEFT:
				newPos.SetHCell(currentPos.HCell() + 2);
				break;
			case RIGHT:
				newPos.SetHCell(currentPos.HCell() - 2);
				break;
			}
			break;

		case MOVE_BACKWARD_THREE_STEPS:
			switch (currDirection) {
			case UP:
				newPos.SetVCell(currentPos.VCell() + 3);
				break;
			case DOWN:
				newPos.SetVCell(currentPos.VCell() - 3);
				break;
			case LEFT:
				newPos.SetHCell(currentPos.HCell() + 3);
				break;
			case RIGHT:
				newPos.SetHCell(currentPos.HCell() - 3);
				break;
			}
			break;
		case ROTATE_CLOCKWISE:
			RotateClockwise(pGrid);
			break;
		case ROTATE_COUNTERCLOCKWISE:
			RotateCounterClockwise(pGrid);
			break;
		default:
			break;
		}
		if (!newPos.IsValidCell())
		{
			pOut->PrintMessage("Invalid Move! Click inside the grid to continue.");
			while (true)
			{
				pIn->GetPointClicked(x, y);
				if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
				{
					// Valid grid click
					pOut->ClearStatusBar();
					break;
				}
				else
				{
					pOut->PrintMessage("Invalid click! Click inside the grid area.");
				}
			}
			continue; // Skip this command and continue with the next
		}
		pGrid->UpdatePlayerCell(this, newPos);

		if (i < maxCommands - 1 && moveCommands[i + 1] != NO_COMMAND)
		{
			pOut->PrintMessage("Click inside the grid to execute the next command.");
			while (true)
			{
				pIn->GetPointClicked(x, y);
				if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
				{
					// Valid grid click
					pOut->ClearStatusBar();
					break;
				}
				else
				{
					pOut->PrintMessage("Invalid click! Click inside the grid area.");
				}
			}
		}
	}
	Cell* finalCell = pGrid->GetCell(pCell->GetCellPosition());
	GameObject* obj = finalCell->GetGameObject();
	if (obj != nullptr)
	{
		obj->Apply(pGrid, this);
	}
	///TODO: Implement this function using the guidelines mentioned below

	// - If a player has 5 (could have less) saved moveCommands, the robot will execute the first saved command,
	//		then wait for a mouse click (display a message "Click anywhere to execute the next command").
	//		After executing all the 5 saved commands, the game object effect at the final destination cell will
	//		be applied.
	// 
	// - Use the CellPosition class to help you calculate the destination cell using the current cell
	// - Use the Grid class to update pCell
	// - Don't forget to apply game objects at the final destination cell and check for game ending

}

void Player::RebootAndRepair(Grid* pGrid)
{
	Output*pOut = pGrid->GetOutput(); 
	if (health < 10) {  
		health = 10;
		pOut->PrintMessage("Reboot and Repair: Health restored to maximum!");
	}
	else {
		pOut->PrintMessage("Reboot and Repair: Health is already at maximum.");
	}

	// Move the player to the starting position
	Cell* startingCell = pGrid->GetStartingCell();
	if (!startingCell)
	{
		pOut->PrintMessage("ERROR: Invalid starting cell");
		return;
	}
	ClearDrawing(pOut);
	SetCell(startingCell); 
	Draw(pOut);
	setInactive(); //skip actions for player
	pGrid->DisPlayerInfo();
	pOut->PrintMessage("player is successfully rebooted"); 
}

void Player::DisplayRandomCommands(Grid* pGrid, Command availableCommands[]) { 
	Output* pOut = pGrid->GetOutput();

	Command commandPool[8] = {
		MOVE_FORWARD_ONE_STEP, MOVE_FORWARD_TWO_STEPS, MOVE_FORWARD_THREE_STEPS,
		MOVE_BACKWARD_ONE_STEP, MOVE_BACKWARD_TWO_STEPS, MOVE_BACKWARD_THREE_STEPS,
		ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWISE
	};

	string commandList = "Available Commands: ";

	//  10 random commands
	for (int i = 0; i < 10; i++) {
		int randomIndex = rand() % 8;
		availableCommands[i] = commandPool[randomIndex];
		commandList += CommandToString(availableCommands[i]) + (i < 9 ? ", " : "");
	}

	pOut->PrintMessage(commandList); 
}

int Player::GetAvailableCommandCount() const
{
	return availableCommandCount;
}

Command* Player::GetAvailableCommands() 
{
	return availableCommands;  
}

string Player::CommandToString(Command cmd) const
{
	switch (cmd) {
	case MOVE_FORWARD_ONE_STEP:
		return "Move Forward 1 Step";
	case MOVE_FORWARD_TWO_STEPS:
		return "Move Forward 2 Steps";
	case MOVE_FORWARD_THREE_STEPS:
		return "Move Forward 3 Steps";
	case MOVE_BACKWARD_ONE_STEP:
		return "Move Backward 1 Step";
	case MOVE_BACKWARD_TWO_STEPS:
		return "Move Backward 2 Steps";
	case MOVE_BACKWARD_THREE_STEPS:
		return "Move Backward 3 Steps";
	case ROTATE_CLOCKWISE:
		return "Rotate Clockwise";
	case ROTATE_COUNTERCLOCKWISE:
		return "Rotate Counterclockwise";
	default:
		return "No Command";
	}
}

void Player::SelectCommands(Grid* pGrid, Command availableCommands[]) { 
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	int maxCommands = (health < 5) ? health : 5; // Limit commands by health
	Command selectedCommands[5]; // To store player's selected commands
	int numSelected = 0;

	pOut->PrintMessage("Select up to " + to_string(maxCommands) + " commands. Click the command bar to select.");

	for (int i = 0; i < maxCommands; i++) {
		int commandIndex = pIn->GetSelectedCommandIndex(); // Get the clicked command index
		if (commandIndex < 0 || commandIndex >= 10) { // Ensure valid selection
			pOut->PrintMessage("Invalid selection. Selection ended.");
			break;
		}

		selectedCommands[numSelected++] = availableCommands[commandIndex];
		pOut->PrintMessage("Command " + to_string(i + 1) + " selected: " + CommandToString(availableCommands[commandIndex]));
	}

	// Save selected commands for execution
	SaveCommands(selectedCommands, numSelected);

	if (numSelected == 0) {
		pOut->PrintMessage("No commands selected. Previous saved commands will be used.");
	}
	else {
		pOut->PrintMessage(to_string(numSelected) + " commands saved.");
	}
}
 
Command* Player::GetSavedCommands()
{
	return savedCommands;
}

int Player::GetSavedCommandCount() const
{
	return savedCommandCount; 
}

void Player::SaveCommands(const Command commands[], int count) {
	count = (count > 5) ? 5 : count;

	for (int i = 0; i < count; i++) {
		this->savedCommands[i] = commands[i]; 
	}

	this->savedCommandCount = count;
}

Direction Player::GetDirection() const
{
	return currDirection;
}

void Player::RotateClockwise(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	ClearDrawing(pOut);

	
		if (currDirection == UP)
			currDirection = RIGHT;
		else if (currDirection == RIGHT)
			currDirection = DOWN;
		else if (currDirection == DOWN)
			currDirection = LEFT;
		else if (currDirection == LEFT)
			currDirection = UP;
	
	Draw(pOut);
}

void Player::RotateCounterClockwise(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	ClearDrawing(pOut);
	
		if (currDirection == UP)
			currDirection = LEFT;
		else if (currDirection == LEFT)
			currDirection = DOWN;
		else if (currDirection == RIGHT)
			currDirection = UP;
		else if (currDirection == DOWN)
			currDirection = RIGHT;
	
	Draw(pOut);
}

string Player::GetPlayerInfo() const
{
	string playerInfo = "P" + to_string(playerNum) + "(";
	CellPosition p = pCell->GetCellPosition();
	playerInfo += to_string(p.GetCellNum()) + ", ";
	string direction;
	switch (currDirection)
	{
	case UP:
		playerInfo += "UP";
		break;
	case DOWN:
		playerInfo += "DOWN";
		break;
	case LEFT:
		playerInfo += "LEFT";
		break;
	case RIGHT:
		playerInfo += "RIGHT";
		break;
	default:
		playerInfo += "Unknown";
		break;
	}
	playerInfo += ", " + to_string(health) + ")";
	return playerInfo;
}

void Player::setInactive()
{
	isActive = false;
}
void Player::UseToolkit(Grid* pGrid) {
	Output* pOut = pGrid->GetOutput();

	if (!hasToolkit) {
		pOut->PrintMessage("No toolkit available to use.");
		return;
	}

	health = 10;
	hasToolkit = false; // toolkit is consumed
	pOut->PrintMessage("Toolkit used! Health fully restored to 10.");
}

void Player::UseHackDevice(Grid* pGrid) {
	Output* pOut = pGrid->GetOutput();

	if (!hasHackDevice) {
		pOut->PrintMessage("No hack device available to use.");
		return;
	}

	for (int i = 0; i < MaxPlayerCount; i++) {
		Player* opponent = pGrid-> GetCurrentPlayer();
		if (opponent != this) { //dont hack itself
			opponent->setInactive(); //hack other player
		}
	}
	hasHackDevice = false; //  device is consumed
	pOut->PrintMessage("Hack device used! Opponents cannot play this round.");
}

void Player::resetForNextRound()
{
	isActive = true;
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	// TODO: Modify the Info as needed

	playersInfo += GetPlayerInfo();
}

int Player:: GetPlayerNumber() const {
	return playerNum;
}