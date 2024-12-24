#pragma once
#include "GameObject.h"
class RotatingGear : public GameObject
{
	bool isClockWise; // if it is true then direction is clockwise, if it is false then direction is anticlockwise
public:
	RotatingGear(const CellPosition & gearposition,bool clockwise); // A constructor for initialization
	virtual GameObject* Copy() const override;

	RotatingGear();

	virtual void Draw(Output* pOut) const; // Draws a rotating gear in a selected cell
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the flag
	bool GetisClockWise() const; // Getter for the direction
	virtual ~RotatingGear();
	void Load(ifstream& InFile) override;
	void Save(ofstream& OutFile, int Type) override; // Saves the flag
	int GetType() const override;
};

