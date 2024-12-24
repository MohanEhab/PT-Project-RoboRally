#ifndef USE_TOOLKIT_ACTION_H
#define USE_TOOLKIT_ACTION_H

#include "Action.h"

class UseToolKitAction : public Action
{
public:
    UseToolKitAction(ApplicationManager* pApp); // Constructor
    virtual void ReadActionParameters();       // Reads parameters (if needed)
    virtual void Execute();                    // Executes the action
    virtual ~UseToolKitAction();               // Destructor
};

#endif // USE_TOOLKIT_ACTION_H
