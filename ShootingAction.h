#pragma once
#include "Action.h"
#include "Player.h"
#include "Grid.h"
#include "ApplicationManager.h"

class ShootingAction: public Action
{
public:
	ShootingAction(ApplicationManager* pApp);
	virtual~ShootingAction();
	virtual void ReadActionParameters();
	virtual void Execute();
};

