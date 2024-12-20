#pragma once
#include "Action.h"
class ApplicationManager;
class ToPlayModeAction : public Action //everyth in action is accessible now

{
public:
	ToPlayModeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ~ToPlayModeAction(); //calls it first then action
};

