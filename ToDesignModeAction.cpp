#include "ToDesignModeAction.h"
#include "Output.h"
#include "Grid.h"
#include "ApplicationManager.h"

ToDesignModeAction::ToDesignModeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void ToDesignModeAction::ReadActionParameters()
{
}

void ToDesignModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); //gives access to grid
	Output* pOut = pGrid->GetOutput(); //gives access to pOut
	pOut->CreateDesignModeToolBar(); //switches to design mode
}

ToDesignModeAction::~ToDesignModeAction()
{
}
