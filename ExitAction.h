#pragma once
#include "Action.h"
class ApplicationManager;
class ExitAction :public Action

{
public:
	ExitAction(ApplicationManager* pApp);
	virtual void ReadActionParameters()override;
	virtual void Execute()override;
	virtual ~ExitAction();

};

