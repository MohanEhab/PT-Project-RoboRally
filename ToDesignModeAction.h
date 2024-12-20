#pragma once
#include "Action.h"
class ApplicationManager;
class ToDesignModeAction :public Action
{
public:
	ToDesignModeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ~ToDesignModeAction();
};

