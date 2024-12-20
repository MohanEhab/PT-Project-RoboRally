#pragma once
#include "Action.h"
class RebootAndRepairAction :public Action
{
public:
	RebootAndRepairAction(ApplicationManager* pApp);
	virtual void ReadActionParameters()override;
	virtual void Execute();
	virtual ~RebootAndRepairAction();
};

