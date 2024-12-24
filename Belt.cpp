#include "Belt.h"
#include "CellPosition.h"
#include "ApplicationManager.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "AddBeltAction.h"

Belt::Belt(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Belt::Draw(Output* pOut) const
{
	pOut->DrawBelt(position, endCellPos);
}
void Belt::Load(ifstream& InFile) {
	int startCellNum, endCellNum;
	InFile >> startCellNum >> endCellNum;
	position = CellPosition::GetCellPositionFromNum(startCellNum);
	endCellPos = CellPosition::GetCellPositionFromNum(endCellNum);
}
int Belt::GetType() const
{
	return 4;
}
Belt::Belt() : GameObject(CellPosition()), endCellPos(CellPosition()) {
	// Initialize with default positions
}
void Belt::Save(ofstream& OutFile, int Type)
{
	if (Type == GetType()) { //4 represents Belt is saved fourth
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
	}
}
void Belt::Apply(Grid* pGrid, Player* pPlayer)
{

	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a belt. Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput(); 
	int x, y;
	pOut->PrintMessage("You have reached a belt. Click to continue...");
	pIn->GetPointClicked(x, y); // Wait for the user to click
	pOut->ClearStatusBar();
	// 2- Apply the belt's effect by moving the player to the endCellPos
	 pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	//    Review the "pGrid" functions and decide which function can be used for that
	
}
CellPosition Belt::GetEndPosition() const
{
	return endCellPos;
}
GameObject* Belt::Copy() const
{
	return new Belt(*this);  // Use copy constructor to create a copy of Belt
}

Belt::~Belt()
{
}
