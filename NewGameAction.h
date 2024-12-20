#pragma once
#include "Action.h"
class ApplicationManager;
class NewGameAction :public Action
{
public:
	NewGameAction(ApplicationManager* pApp);
	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ~NewGameAction();
};

