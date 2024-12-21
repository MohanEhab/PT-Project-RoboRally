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
			continue;
		case ROTATE_COUNTERCLOCKWISE:
			RotateCounterClockwise(pGrid);
			continue;
		default:
			continue;
		}
		if (!newPos.IsValidCell())
		{
			pOut->PrintMessage("Invalid Move.");
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			return;
		}
		pGrid->UpdatePlayerCell(this, newPos);

		if (i < maxCommands - 1 && moveCommands[i + 1] != NO_COMMAND)
		{
			pOut->PrintMessage("Click anywhere to execute the next command.");
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
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
	Cell* start = pGrid->GetStartingCell(); //gets starting cell
	ClearDrawing(pGrid->GetOutput()); //clears recent drawing 
	SetCell(start); //player on new cell now
	Draw(pGrid->GetOutput()); //redraws player on cell
	health = 10; //max health
	pGrid->DisPlayerInfo();
}

void Player::ExecuteCommand(Command* command, int commandCount, Grid* pGrid)
{
	CellPosition currentPos = pCell->GetCellPosition();
	CellPosition newPos;
	for (int i = 0; i < commandCount; i++)
	{
		switch (command[i])
		{
		case MOVE_FORWARD_ONE_STEP:
			stepCount = 1;
			break;
		case MOVE_BACKWARD_ONE_STEP:
			stepCount = -1;
			break;
		case MOVE_FORWARD_TWO_STEPS:
			stepCount = 2;
			break;
		case MOVE_BACKWARD_TWO_STEPS:
			stepCount = -2;
			break;
		case MOVE_FORWARD_THREE_STEPS:
			stepCount = 3;
			break;
		case MOVE_BACKWARD_THREE_STEPS:
			stepCount = -3;
			break;
		case ROTATE_CLOCKWISE:
			RotateClockwise(pGrid);
			break;
		case ROTATE_COUNTERCLOCKWISE:
			RotateCounterClockwise(pGrid);
			break;
		case NO_COMMAND:
		default:
			return;
		}
	}
	for (int i = 0; i < abs(stepCount); i++)
	{

		switch (currDirection)
		{
		case RIGHT:
			newPos.SetHCell(newPos.HCell() + 1);
			break;
		case LEFT:
			newPos.SetHCell(newPos.HCell() - 1);
			break;
		case DOWN:
			newPos.SetVCell(newPos.VCell() + 1);
			break;
		case UP:
			newPos.SetVCell(newPos.VCell() - 1); //dec count of VCELL
			break;
		}
		if (!newPos.IsValidCell())
		{
			pGrid->PrintErrorMessage("you're out of bound, movement is stopped");
			return;
		}
	}
	pGrid->UpdatePlayerCell(this, newPos);
	pGrid->DisPlayerInfo();
}
Direction Player::GetDirection() const
{
	return currDirection;
}
void Player::RotateClockwise(Grid *pGrid)
{
	Output* pOut = pGrid->GetOutput();
	ClearDrawing(pOut);

	switch (currDirection)
	{
		if (currDirection == UP)
			currDirection = RIGHT;
		else if (currDirection == RIGHT)
			currDirection = DOWN;
		else if (currDirection == DOWN)
			currDirection = LEFT;
		else if (currDirection == LEFT)
			currDirection = UP;
		break;
	default:
		break;
	}
	Draw(pOut);
}

void Player::RotateCounterClockwise(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	ClearDrawing(pOut);
	switch (currDirection)
	{
		if (currDirection == UP)
			currDirection = LEFT;
		else if (currDirection == LEFT)
			currDirection = DOWN;
		else if (currDirection == RIGHT)
			currDirection = UP;
		else if (currDirection == DOWN)
			currDirection = RIGHT;
		break;
	default:
		break;
	}
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

void Player::SelectCommands(Grid* pGrid)
{
	int maxC = (health < 5) ? health : 5;
	Command selectedCommands[5];
	pGrid->GetOutput()->PrintMessage("select your command (click command bar)");
	for (int i = 0; i < maxC; i++)
	{
		int commandSet = pGrid->GetInput()->GetSelectedCommandIndex();
		switch (commandSet)
		{
		case 0:
			selectedCommands[i] = MOVE_FORWARD_ONE_STEP;
			break;
		case 1:
			selectedCommands[i] = MOVE_FORWARD_TWO_STEPS;
			break;
		case 2:
			selectedCommands[i] = MOVE_FORWARD_THREE_STEPS;
			break;
		case 3:
			selectedCommands[i] = MOVE_BACKWARD_ONE_STEP;
			break;
		case 4:
			selectedCommands[i] = MOVE_BACKWARD_TWO_STEPS;
			break;
		case 5:
			selectedCommands[i] = MOVE_BACKWARD_THREE_STEPS;
			break;
		case 6:
			selectedCommands[i] = ROTATE_CLOCKWISE;
			break;
		case 7:
			selectedCommands[i] = ROTATE_COUNTERCLOCKWISE;
			break;
		default:
			selectedCommands[i] = NO_COMMAND;
			break;
		}
		pGrid->GetOutput()->PrintMessage("command" + to_string(i + 1) + "selected");
	}
	ExecuteCommand(selectedCommands, maxC, pGrid);

}
void Player::AppendPlayerInfo(string & playersInfo) const
{
	// TODO: Modify the Info as needed
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(currDirection) + ", ";
	playersInfo += to_string(health) + ")";

}

int Player:: GetPlayerNumber() const {
	return playerNum;
}