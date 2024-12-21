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
	
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		CellPosition startPos(0, i);
		Cell* startCell = pGrid->GetCell(startPos);
		Player* newPlayer = new Player(startCell, i);
	}

	pOut->PrintMessage("switched to play mode");
	Command savedCommands[5];
	Command availableCommands[10];
	savedCommands[0] = MOVE_FORWARD_ONE_STEP;
	savedCommands[1] = MOVE_BACKWARD_ONE_STEP;
	savedCommands[2] = MOVE_FORWARD_TWO_STEPS;
	savedCommands[3] = MOVE_BACKWARD_TWO_STEPS;
	savedCommands[4] = MOVE_FORWARD_THREE_STEPS;



	availableCommands[0] = MOVE_FORWARD_ONE_STEP;
	availableCommands[1] = MOVE_FORWARD_TWO_STEPS;
	availableCommands[2] = NO_COMMAND;
	availableCommands[3] = NO_COMMAND;
	availableCommands[4] = NO_COMMAND;
	availableCommands[5] = NO_COMMAND;
	availableCommands[6] = NO_COMMAND;
	pOut->CreateCommandsBar(savedCommands, 5, availableCommands, 7);


}