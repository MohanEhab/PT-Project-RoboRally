#pragma once
#include "GameObject.h"
class WaterPit:public GameObject
{
public:
	WaterPit(const CellPosition& waterPitPosition); // A constructor for initialization
	WaterPit();
	virtual void Draw(Output* pOut) const; // Draws a water pit in the cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the waterPit by killing the robot instantly and ending the game
	void Save(ofstream& OutFile, int Type) override; // Saves the flag
	void Load(ifstream& InFile) override;
	virtual GameObject* Copy() const override; // Override Copy function
	int GetType() const override;
	virtual ~WaterPit();
};

