#ifndef UNIFIED_ACTION_HANDLER_H
#define UNIFIED_ACTION_HANDLER_H

#include "ApplicationManager.h"
#include "UseHackAction.h"
#include "UseToolKitAction.h"
#include "RebootAndRepairAction.h"
// Include other required action headers

class UnifiedActionHandler {
private:
    ApplicationManager* pAppManager; // Pointer to ApplicationManager
public:
    UnifiedActionHandler(ApplicationManager* appManager);

    // Process and handle the given action
    void HandleAction(ActionType ActType);

    ~UnifiedActionHandler();
};

#endif // UNIFIED_ACTION_HANDLER_H
