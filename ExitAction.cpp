#include "ExitAction.h"
#include "Grid.h"
#include "ApplicationManager.h"

ExitAction::ExitAction(ApplicationManager* pApp) :Action(pApp)
{}

void ExitAction::ReadActionParameters()
{}

void ExitAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	pGrid->PrintErrorMessage("Exiting the game, Bye. ;)");
}

ExitAction::~ExitAction()
{}
