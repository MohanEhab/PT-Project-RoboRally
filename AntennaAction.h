#pragma once
#include "Action.h"
#include "Player.h"
#include "Grid.h"
#include "ApplicationManager.h"
#include "Output.h"

class AntennaAction : public Action
{
public:
	AntennaAction(ApplicationManager* pApp);
	virtual~AntennaAction();
	virtual void Execute();
};


