#include "UnifiedActionHandler.h"
#include "Grid.h"
#include "Player.h"
#include"UseHackAction.h"
#include"ToPlayModeAction.h"
UnifiedActionHandler::UnifiedActionHandler(ApplicationManager* appManager)
    : pAppManager(appManager)
{}

void UnifiedActionHandler::HandleAction(ActionType ActType)
{
    Grid* pGrid = pAppManager->GetGrid(); 
    Player* currentPlayer = pGrid->GetCurrentPlayer(); 

    switch (ActType)
    {
    case USE_HACK:
        if (currentPlayer->HasHackDevice()) {
            UseHackAction hackAction(pAppManager);
            hackAction.Execute();
        }
        break;

    case USE_TOOLKIT:
        if (currentPlayer->HasToolkit()) {
            UseToolKitAction toolkitAction(pAppManager);
            toolkitAction.Execute();
        }
        break;

    case REBOOT_AND_REPAIR:
        if (currentPlayer->NeedsRebootAndRepair()) {
            RebootAndRepairAction rebootAction(pAppManager);
            rebootAction.Execute();
        }
        break;


    default:
        pAppManager->ExecuteAction(ActType);
        break;
    }
}

UnifiedActionHandler::~UnifiedActionHandler() {}
