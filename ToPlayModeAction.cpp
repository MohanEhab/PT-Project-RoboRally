#include "ToPlayModeAction.h"
#include "ApplicationManager.h"
#include "Output.h"
#include "Grid.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}
ToPlayModeAction::~ToPlayModeAction() {}

void ToPlayModeAction::ReadActionParameters()
{
}

void ToPlayModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); //access to grid
	Output* pOut = pGrid->GetOutput(); //access to pOut
	pOut->CreatePlayModeToolBar(); //switches the mode
}
