#include "RebootAndRepairAction.h"
#include"ApplicationManager.h"
#include"Grid.h"
#include"Player.h"

#include "RebootAndRepairAction.h"
RebootAndRepairAction::RebootAndRepairAction(ApplicationManager* pApp) :Action(pApp)
{}

void RebootAndRepairAction::ReadActionParameters()
{}

void RebootAndRepairAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); //gets current grid 
	Player* currentPlayer = pGrid->GetCurrentPlayer(); //gets current player
	currentPlayer->RebootAndRepair(pGrid); //calls func
	pGrid->GetOutput()->PrintMessage("player rebooted and repaired");
}

RebootAndRepairAction::~RebootAndRepairAction()
{}

