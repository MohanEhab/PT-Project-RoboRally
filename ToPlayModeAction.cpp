#include "ToPlayModeAction.h"
#include "ApplicationManager.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}
ToPlayModeAction::~ToPlayModeAction() {}

void ToPlayModeAction::ReadActionParameters()
{
}

void ToPlayModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); //access to grid
	Output* pOut = pGrid->GetOutput(); //access to pOut
	pOut->CreatePlayModeToolBar(); //switches the mode
	Player* players[2];
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		CellPosition startPos(0, i);
		Cell* startCell = pGrid->GetCell(startPos);
		players[i] = new Player(startCell, i);
	}
	pGrid->DisPlayerInfo();
	pOut->PrintMessage("Switched to Play Mode");
	Player* currentPlayer = pGrid->GetCurrentPlayer();
	// Generate and display random commands
	currentPlayer->DisplayRandomCommands(pGrid);
	// Retrieve available commands
	int availableCommandsCount = currentPlayer->GetSavedCommandCount();

	// Use the generated commands in the commands bar
    Command savedCommands[5] = { NO_COMMAND, NO_COMMAND, NO_COMMAND, NO_COMMAND, NO_COMMAND };
	Command availableCommands[8] = {
		MOVE_FORWARD_ONE_STEP, MOVE_FORWARD_TWO_STEPS, MOVE_FORWARD_THREE_STEPS,
		MOVE_BACKWARD_ONE_STEP, MOVE_BACKWARD_TWO_STEPS, MOVE_BACKWARD_THREE_STEPS,
		ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWISE
	};
	pOut->CreateCommandsBar(savedCommands, 5, availableCommands, 8);	

	// Let the player select commands
	currentPlayer->SelectCommands(pGrid);

	// Execute the selected commands
	currentPlayer->Move(pGrid, savedCommands);
}