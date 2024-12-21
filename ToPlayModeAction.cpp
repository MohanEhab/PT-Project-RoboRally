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
	int numPlayers = 2;
	for (int i = 0; i < numPlayers; i++)
	{
		CellPosition startPos(0, i);
		Cell* startCell = pGrid->GetCell(startPos);
		Player* newPlayer = new Player(startCell, i);
	}
	pOut->PrintMessage("switched to play mode");


}