#include "UseToolKitAction.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
#include "ApplicationManager.h"

UseToolKitAction::UseToolKitAction(ApplicationManager* pApp) : Action(pApp)
{
}

void UseToolKitAction::ReadActionParameters()
{
}

void UseToolKitAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();   
    Player* currentPlayer = pGrid->GetCurrentPlayer(); 

    if (!currentPlayer)
        return;

    currentPlayer->UseToolkit(pGrid); 
    pGrid->PrintErrorMessage("Toolkit is used. Click to continue");
}

UseToolKitAction::~UseToolKitAction()
{
}
