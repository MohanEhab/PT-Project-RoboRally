#pragma once
#include "GameObject.h"
class Workshop :
	public GameObject
{
	int repairAmount; // Holds the repair value for the workshop
public:
	Workshop(const CellPosition & workshopPosition);
	virtual void Draw(Output* pOut) const; // Draws workshop

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the workshop
	void Save(ofstream& OutFile, int Type) override; // Saves the flag
	void Load(ifstream& InFile) override;
	virtual GameObject* Copy() const override;
	Workshop();
	Workshop(const CellPosition& pos, int repairAmt);
	int GetType() const override;
	~Workshop();
};

