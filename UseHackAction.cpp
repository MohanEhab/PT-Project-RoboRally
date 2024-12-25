#include "UseHackAction.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
#include "ApplicationManager.h"

UseHackAction::UseHackAction(ApplicationManager* pApp) : Action(pApp)
{}

void UseHackAction::ReadActionParameters()
{}

void UseHackAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();       
    Player* currentPlayer = pGrid->GetCurrentPlayer(); 
    currentPlayer->UseHackDevice(pGrid);     
    pGrid->PrintErrorMessage("Hack Device is used. Click to Continue");

}

UseHackAction::~UseHackAction()
{}
