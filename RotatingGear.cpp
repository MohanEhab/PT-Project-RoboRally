#include "RotatingGear.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "AddRotatingGearAction.h"
using namespace std;




RotatingGear::RotatingGear(const CellPosition& gearposition, bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}
GameObject* RotatingGear::Copy() const
{
	return new RotatingGear(*this); // Use the copy constructor
}
RotatingGear::RotatingGear() : GameObject(), isClockWise(true) {
	position.SetVCell(0);
	position.SetHCell(0);
}
void RotatingGear::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message and change the message according to direction of rotation "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (isClockWise)
		pOut->PrintMessage("You have reached a rotating gear, you will rotate clockwise. Click to continue...");
	else
		pOut->PrintMessage("You have reached a rotating gear, you will rotate anti-clockwise. Click to continue...");

	int x, y;
	pIn->GetPointClicked(x, y);
	//2- Apply the roating gear's effect by rotating the player according to the direction
	if(isClockWise)
		pPlayer->RotateClockwise(pGrid);
	else
		pPlayer->RotateCounterClockwise(pGrid);
		
	// Clear the message after applying the effect
	pOut->ClearStatusBar();
}

bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}
void RotatingGear::Load(ifstream& InFile)
{
	int cellNum, rotationDirection;
	InFile >> cellNum >> rotationDirection;// Read position
	position = CellPosition::GetCellPositionFromNum(cellNum); // Convert cell number to position

	isClockWise = (rotationDirection == 1);// 1 for clockwise, 0 for counterclockwise
}

void RotatingGear::Save(ofstream& OutFile, int Type)
{
	if (Type == GetType()) { // Assuming 4 represents RotatingGears
		OutFile << position.GetCellNum() << " " << (isClockWise ? 1 : 0) << endl;
	}
}

int RotatingGear::GetType() const
{
	return 7;
}

RotatingGear::~RotatingGear()
{
}