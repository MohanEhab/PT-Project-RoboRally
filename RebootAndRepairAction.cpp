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
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	Player* currentPlayer = pGrid->GetCurrentPlayer(); //gets current player
	currentPlayer->RebootAndRepair(pGrid); //calls func
	pGrid->GetOutput()->PrintMessage("Player is rebooted and repaired, Click to continue");
	currentPlayer->setActive();
	pIn->GetPointClicked(x, y); // Wait for the user to click
	pOut->ClearStatusBar();
}

RebootAndRepairAction::~RebootAndRepairAction()
{}