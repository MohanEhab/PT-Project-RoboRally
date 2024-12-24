#include "Flag.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
Flag::Flag(const CellPosition& flagposition, int score): GameObject(flagposition), scoreValue(score)
{
}

Flag::Flag(const Flag& other) : GameObject(other.position) {
	this->scoreValue = other.scoreValue; // Copy the score value
}

Flag::Flag() : GameObject() {
	scoreValue = 0; // Initialize the scoreValue to a default value
}

void Flag::Draw(Output* pOut) const
{
	pOut->DrawFlag(position);
}

void Flag::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a flag. Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	// 2- Apply the flag's effect by ending the game
	int Winner = pPlayer->GetPlayerNumber() + 1;
	pOut->PrintMessage("Player " + to_string(Winner) + " reached the flag and Wins!  Click to continue...");
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	pOut->PrintMessage("Start a new Game.");
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	pGrid->SetEndGame(true);
	//    Review the "pGrid" functions and decide which function can be used for that
}

void Flag::Save(ofstream& OutFile, int Type)
{
	if (Type == GetType()) { // Type 1 correspond to Flags saves flag first
		OutFile << position.GetCellNum() << " " << scoreValue << endl;
	}
}

void Flag::Load(std::ifstream& InFile)
{
	{
		int cellNum,scorevalue;
		InFile >> cellNum >> scorevalue;
		position = CellPosition::GetCellPositionFromNum(cellNum);
	}

}

GameObject* Flag::Copy() const
{
	return new Flag(*this);
}

int Flag::GetType() const
{
	return 1;
}

Flag::~Flag()
{

}