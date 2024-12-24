#pragma once
#include "GameObject.h"
class Flag :public GameObject
{
	int scoreValue;//Represents the score value awarded when a player collects this flag.
public:
	Flag(const CellPosition& flagposition, int score = 0); // updated constructor
	Flag(const Flag& other);
	Flag();
	virtual void Draw(Output* pOut) const; // Draws a flag in a selected cell
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the flag
	virtual ~Flag(); // Virtual destructor
	void Save(ofstream& OutFile, int Type) override; // Saves the flag
	virtual void Load(std::ifstream& InFile) override; // Loads the flag
	virtual GameObject* Copy() const override;
	int GetType() const override;
};