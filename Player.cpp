#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0),
health(10), playerNum(playerNum), currDirection(RIGHT),
hasDoubleLaser(false),hasExtendedMemory(false), 
hasToolkit(false),hasHackDevice(false), 
equippedLaser(BASIC_LASER), hasShield(false), 
hasLaserReflection(false), isRebootnRepair(false),isActive(true)
{
	this->pCell = pCell;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======
bool Player::HasRebootnRepair() {
	return isRebootnRepair;
}

void Player::setRebootnRepair(bool n) {
	isRebootnRepair = n;
}

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
void Player::EnableLaserReflection() {
	hasLaserReflection = true;
}

void Player::setSkipNextRound(int rounds)
{
	skipRounds = rounds;
}

bool Player::shouldSkipThisTurn() const
{
	return skipRounds>0;
}

void Player::decrementSkipRounds()
{
	if (skipRounds > 0) { skipRounds--; }
}

bool Player::HasLaserReflection() const {
	return hasLaserReflection;
}

void Player::DisableLaserReflection() {
	hasLaserReflection = false;
}

void Player::EnableShield() {
	hasShield = true;
}

bool Player::HasShield() const {
	return hasShield;
}

void Player::DisableShield() {
	hasShield = false;
}

void Player::EquipLaser(LaserType laser) {
	equippedLaser = laser;
}

void Player::EquipDoubleLaser() {
	
	EquipLaser(DOUBLE_LASER);
	hasDoubleLaser = true;
}

bool Player::NeedsRebootAndRepair() const
{
	return (health < 10); 
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

void Player::AddToolkit() 
{
	
	hasToolkit = true;
}

bool Player::HasToolkit() const
{
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
	if (pCell)
		pOut->DrawCell(pCell->GetCellPosition(), cellColor);
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	GameObject* obj = pCell->GetGameObject();
	if (obj) obj->Draw(pOut);
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, Command moveCommands[])
{
	int x, y;
	if (!isActive) return;
	int extra = (this->HasExtendedMemory()) ? 1 : 0;
	int maxCommands =  5 + extra;	
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
				newPos.SetVCell(currentPos.VCell() - 1); // Move up
				break;
			case DOWN:
				newPos.SetVCell(currentPos.VCell() + 1); // Move down
				break;
			case LEFT:
				newPos.SetHCell(currentPos.HCell() - 1); // Move left
				break;
			case RIGHT:
				newPos.SetHCell(currentPos.HCell() + 1); // Move right
				break;
			}
			break;
		case MOVE_FORWARD_TWO_STEPS:
			switch (currDirection) {
			case UP:
				newPos.SetVCell(currentPos.VCell() - 2); // Move up 2 steps
				break;
			case DOWN:
				newPos.SetVCell(currentPos.VCell() + 2); // Move down 2 steps
				break;
			case LEFT:
				newPos.SetHCell(currentPos.HCell() - 2); // Move left 2 steps
				break;
			case RIGHT:
				newPos.SetHCell(currentPos.HCell() + 2); // Move right 2 steps
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
		pGrid->DisPlayerInfo();
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
	Input* pIn = pGrid->GetInput();
	int x, y;
	if (!HasRebootnRepair())  //checks if its rebooted or not
	{
		pOut->PrintMessage("Player Cannot be rebooted or repaired");
		pIn->GetPointClicked(x, y); // Wait for the user to click
		pOut->ClearStatusBar();
		return;
	}
    if (health < 10) {  
		health = 10; //sets health to 10 again
		pOut->PrintMessage("Reboot and Repair: Health restored to maximum!");
		pIn->GetPointClicked(x, y); // Wait for the user to click
		pOut->ClearStatusBar();
	}
	else {
		pOut->PrintMessage("Reboot and Repair: Health is already at maximum.");
		pIn->GetPointClicked(x, y); // Wait for the user to click
		pOut->ClearStatusBar();
	}
	// move the player to the starting position
	Cell* startingCell = pGrid->GetStartingCell();
	currDirection = RIGHT;
	ClearDrawing(pOut);
	SetCell(startingCell); 
	Draw(pOut);
	setSkipNextRound(1);
	isRebootnRepair = false;
	pGrid->DisPlayerInfo();
	// pOut->PrintMessage("Player Rebooted and Repaired successfully"); removed so the message before it would get printed
}

void Player::DisplayRandomCommands(Grid* pGrid, Command availableCommands[]) { 
	Output* pOut = pGrid->GetOutput();

	Command commandPool[8] = //all possible cmds
	{ 
		MOVE_FORWARD_ONE_STEP, MOVE_FORWARD_TWO_STEPS, MOVE_FORWARD_THREE_STEPS,
		MOVE_BACKWARD_ONE_STEP, MOVE_BACKWARD_TWO_STEPS, MOVE_BACKWARD_THREE_STEPS,
		ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWISE
	};

	string commandList = "Available Commands: ";
	int availableCommandsCount = (health < 10) ? health : 10; //no. of av cmds 

	//  10 random commands
	for (int i = 0; i < 10; i++) {
		int randomIndex = rand() % 8; //rand num between 0 and 7
		availableCommands[i] = commandPool[randomIndex]; //assign cmd to av cmd
		commandList += CommandToString(availableCommands[i]) + (i < availableCommandCount-1 ? ", " : "");
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

void Player:: disableExtendedMemory() {
	hasExtendedMemory = false;
}

void Player::SelectCommands(Grid* pGrid, Command availableCommands[])
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (!isActive) return;
	int extra = (this->HasExtendedMemory()) ? 1 : 0;
	int maxCommands = (health < 5) ? health + extra : 5 + extra; // limit commands

	Command* selectedCommands = new Command[maxCommands]; // store player's selected commands
	int numSelected = 0;
	int availableCommandCount = (health<10)? health:10; // initial size of availableCommands array

	pOut->PrintMessage("Select up to " + to_string(maxCommands) + " commands. Click the command bar to select.");
	int commandIndex; //int to represent position of selection on bar 

	do
	{
		do
		{
		commandIndex = pIn->GetSelectedCommandIndex(); // get the clicked command index
		} while (commandIndex == -1); //break if out of bound

		if (commandIndex < 0 || commandIndex >= availableCommandCount) // validation
		{
			pOut->PrintMessage("Invalid selection. Selection ended.");
			break;
		}

		// add selected command to the player's commands
		if (availableCommands[commandIndex] != NO_COMMAND) { //no command maydkholsh
			selectedCommands[numSelected++] = availableCommands[commandIndex]; //selected av to save 3ala tol
			pOut->PrintMessage("Command " + to_string(numSelected) + " selected: " + CommandToString(availableCommands[commandIndex]));
			availableCommands[commandIndex] = NO_COMMAND;
			pOut->CreateCommandsBar(selectedCommands, numSelected, availableCommands, availableCommandCount); //yekhaly el chosen black
		}
	}
	while (numSelected < maxCommands );
	

	// save the selected commands
	SaveCommands(selectedCommands, numSelected); //save for execution (move)

	if (numSelected == 0)
	{
		pOut->PrintMessage("No commands selected. Select Command Now.");
	}
	else
	{
		pOut->PrintMessage(to_string(numSelected) + " commands saved.");
	}

	delete[] selectedCommands;
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
	int extra = (this->HasExtendedMemory()) ? 1 : 0;
	int max_count{ 5 + extra};  //def 5 then add extra
	count = (count > max_count) ? max_count : count; //count should be <max

	for (int i = 0; i < count; i++) {
		this->savedCommands[i] = commands[i];  //commands into savedcommands
	}
	for (int i = count; i < max_count; i++) {
		this->savedCommands[i] = NO_COMMAND; //all unsaved spaces yeb2o keda
	} // to save the rest as NO_COMMAND as to be called in the execute func

	this->savedCommandCount = count; //save total no. of commands
}

Direction Player::GetDirection() const
{
	return currDirection;
}

void Player::RotateClockwise(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	ClearDrawing(pOut); //to clear curr dir

	
		if (currDirection == UP)
			currDirection = RIGHT;
		else if (currDirection == RIGHT)
			currDirection = DOWN;
		else if (currDirection == DOWN)
			currDirection = LEFT;
		else if (currDirection == LEFT)
			currDirection = UP;
	
	Draw(pOut); //draw new dir
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
void Player::setActive()
{
	isActive = true;
}
bool Player::isCurrentlyActive() const
{
	return isActive;
}
void Player::UseToolkit(Grid* pGrid) 
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	if (!HasToolkit()) //add tool kit set it to true, already initialized b false
	{
		pOut->PrintMessage("No Toolkit is available for you ");
		return; 
	}

	health = 10;
	hasToolkit = false; // toolkit is consumed
	pOut->PrintMessage("Toolkit used! Health fully restored to 10.");
	pIn->GetPointClicked(x, y); // Wait for the user to click
	pOut->ClearStatusBar();
	setSkipNextRound(1);
}

void Player::UseHackDevice(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();

	if (!HasHackDevice()) 
	{ 
		pOut->PrintMessage("You don't have a hackdevice.");
		return;
	}
	Player* opponent = pGrid-> GetOpponentPlayer(); 
	opponent->setInactive(); //hack other player
	hasHackDevice = false; //  device is consumed
	pOut->PrintMessage("Hack device used! Opponents cannot play this round.");
	opponent->setSkipNextRound(1);
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