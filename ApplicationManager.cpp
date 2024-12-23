#include "ApplicationManager.h"
#include "Grid.h"
#include "AddBeltAction.h"
#include "AddRotatingGearAction.h"
#include "AddFlagAction.h"
#include "AddAntenna.h"
#include "AddWaterPit.h"
#include "AddDangerZone.h"
#include "AddWorkshop.h"
#include "Action.h"
#include "ExitAction.h"
#include "NewGameAction.h"
#include "ToDesignModeAction.h"
#include "RebootAndRepairAction.h"
#include "ToPlayModeAction.h"
#include"SelectPlayerMovementAction.h"
#include "ExecutePlayerMovementAction.h"

///TODO: Add #include for all action types

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
	if (UI.InterfaceMode == MODE_PLAY)
		pGrid->DisPlayerInfo();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case SET_BELT:
		pAct = new AddBeltAction(this);
		break;

	case SET_ROTATING_GEAR:
		// create an object of AddRotatingGearAction here
		pAct = new AddRotatingGearAction(this);
		break;
	case SET_FLAG_CELL:
		// create an object of AddFlagAction here
		pAct = new AddFlagAction(this);
		break;

	case SET_ANTENNA_CELL:
		pAct = new AddAntenna(this);
		break;

	case SET_WATER_PIT:
		pAct = new AddWaterPit(this);
		break;

	case SET_DANGER_ZONE:
		pAct = new AddDangerZone(this);
		break;

	case SET_WORKSHOP:
		pAct = new AddWorkshop(this);
		break;

	case EXIT:
		pAct = new ExitAction(this);
		break;

	case NEW_GAME:
		pAct = new NewGameAction(this);
		break;

	case TO_PLAY_MODE:
		pAct = new ToPlayModeAction(this);
		break;

	case REBOOT_AND_REPAIR:
		pAct = new RebootAndRepairAction(this);
		break;

	case TO_DESIGN_MODE:
		pAct = new ToDesignModeAction(this);
		break;
	case SELECT_COMMAND:
		pAct = new SelectPlayerMovementAction(this);
		break;
	case EXECUTE_COMMANDS:
		pAct = new ExecutePlayerMovementAction(this);
		break;
		

		///TODO: Add a case for EACH Action type in the Design mode or Play mode



	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
