#pragma once
#include "GameObject.h"
class DangerZone:public GameObject
{
public:
	DangerZone(const CellPosition & dangerZonePosition);
	DangerZone();
	virtual void Draw(Output* pOut) const; // Draws a danger zone in the cell
	virtual GameObject* Copy() const override; // Override Copy function
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the danger zone by reducing the robot's health by 1
	void Save(ofstream& OutFile, int Type) override; // Saves the flag
	void Load(ifstream& InFile) override;
	int GetType() const override;
	virtual ~DangerZone();
};

