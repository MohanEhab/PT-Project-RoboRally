#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode
	SET_FLAG_CELL,	// Set Flag on a Cell
	EXIT, // Exits Application
	TO_PLAY_MODE,  //Switches from Design Mode to Play Mode
	SET_ANTENNA_CELL, // Set Antenna on a Grid
	SET_BELT, // Set Belt between Two Selected Cells
	SET_WATER_PIT, //Set Water Pit to Selected Cell
	SET_DANGER_ZONE, // Set Danger Zone to Selected Cell
	SET_WORKSHOP, //Set Workshop on Selected Cell
	SET_ROTATING_GEAR, //Set Rotating Gear to Selected Cell
	COPY_GAME_OBJECT, //Copies Game objected from a Selected Cell
	CUT_GAME_OBJECT, //Cuts Game Object from a Selected Cell
	PASTE_GAME_OBJECT, //Pastes Copied or Cut Object into a Selected Cell
	DELETE_GAME_OBJECT, //Deletes Object in the Selected Cell
	SAVE_GRID, //Saves Current Grid to a File
	LOAD_GRID, //Loads Saved Grid and Displays it on the Grid
	USE_TOOLKIT,
	USE_HACK,






	///TODO: Add more action types of Design Mode

	// [2] Actions of Play Mode
	TO_DESIGN_MODE,	// Go to Design Mode
	SELECT_COMMAND, //Select a command from the available ones
	EXECUTE_COMMANDS, //Executes saved command 
	REBOOT_AND_REPAIR, //Rebotes and repairs the robot
	USE_CONSUMABLE, //Use consumable item
	NEW_GAME, //Restarts the game
	





	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,							// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,						// Inside Grid Area
	STATUS 							// Inside StatusBar Area
};

enum LaserType {
	BASIC_LASER, // Deals 1 point of damage
	DOUBLE_LASER // Deals 2 points of damage 
};

enum Direction // Directions of the game
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum Command
{
	NO_COMMAND,
	MOVE_FORWARD_ONE_STEP,
	MOVE_BACKWARD_ONE_STEP,
	MOVE_FORWARD_TWO_STEPS,
	MOVE_BACKWARD_TWO_STEPS,
	MOVE_FORWARD_THREE_STEPS,
	MOVE_BACKWARD_THREE_STEPS,
	ROTATE_CLOCKWISE,
	ROTATE_COUNTERCLOCKWISE,

	COMMANDS_COUNT,
};

#endif