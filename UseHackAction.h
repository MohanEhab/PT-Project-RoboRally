#ifndef USE_HACK_ACTION_H
#define USE_HACK_ACTION_H

#include "Action.h"

class UseHackAction : public Action
{
public:
    UseHackAction(ApplicationManager* pApp); // Constructor
    virtual void ReadActionParameters();          // Reads parameters (if needed)
    virtual void Execute();                       // Executes the action
    virtual ~UseHackAction();              // Destructor
};

#endif // USE_HACK_DEVICE_ACTION_H
