#include "NewGameAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "Player.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) :Action(pApp) {}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	pGrid->ResetAllPlayers(); //player reset
	pGrid->ClearAllObjects(); //all objects are deleted

	pGrid->UpdateInterface(); //update the game
	pGrid->GetOutput()->PrintMessage("new game started");
}

NewGameAction::~NewGameAction()
{
}
