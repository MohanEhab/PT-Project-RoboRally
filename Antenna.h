#pragma once
#include "GameObject.h"
class Antenna :public GameObject
{
	int signalRange; //  additional attribute for Antenna
public:
	Antenna(const CellPosition & antennaPosition);
	Antenna(); // Default constructor
	virtual void Draw(Output* pOut) const; // Draws an antenna
	virtual GameObject* Copy() const override;
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the antenna by deciding the players turns
	void Load(ifstream& InFile) override;
	void Save(ofstream& OutFile, int Type) override; // Saves the flag
	int GetType() const override;
	virtual ~Antenna();
};

