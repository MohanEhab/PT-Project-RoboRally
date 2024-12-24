#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}
GameObject::GameObject() {
	// Default constructor: initialize position to invalid (-1, -1)
	position.SetVCell(-1);
	position.SetHCell(-1);
}

CellPosition GameObject::GetPosition() const
{
	return position;
}
void GameObject::SetPosition(CellPosition& pos)
{
	position = pos;
}

GameObject::~GameObject()
{
}