#pragma once
#include "Action.h"
#include "Player.h"
#include "Grid.h"
#include "ApplicationManager.h"
#include "Output.h"

class ShootingAction: public Action
{
public:
	ShootingAction(ApplicationManager* pApp);
	virtual~ShootingAction();
	virtual void Execute();
};

