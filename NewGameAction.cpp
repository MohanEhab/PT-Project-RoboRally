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
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	
	pGrid->ResetAllPlayers(); //player reset
	pGrid->ClearAllObjects(); //all objects are deleted

	pGrid->UpdateInterface(); //update the game
	pOut->PrintMessage("New game started, return to design mode...");
}

NewGameAction::~NewGameAction()
{
}
