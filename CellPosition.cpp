#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	if (v >= 0 && v < 5)  ///TODO: Implement this function as described in the .h file (don't forget the validation)
	{
		vCell = v;
		return true;
	}
	else {
		vCell = -1;
		return false; // this line sould be changed with your implementation
		
	}
}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h < 11) {

		hCell = h;
		return true;
	} 
	else {///TODO: Implement this function as described in the .h file (don't forget the validation)
		hCell = -1;
		return false; // this line sould be changed with your implementation
		
	}
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	if (vCell >= 0 && vCell < 5) {
		if (hCell >= 0 && hCell < 11)
		{
			return true;
		}
	}///TODO: Implement this function as described in the .h file

	return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	if (!cellPosition.IsValidCell())
		return -1;   ///TODO: Implement this function as described in the .h file
	int cellnum{0};
	int rowbelow = 4 - cellPosition.vCell;
	cellnum += rowbelow * 11;
	cellnum += cellPosition.hCell + 1;
	return cellnum;
	// this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	if (cellNum < 1 || cellNum>55)
		return CellPosition(-1, -1);
	int vReverse = (cellNum - 1) / 11;
	int vcell = 4 - vReverse;
	int hcell = cellNum - 1;
	while (hcell >= 11) {
		hcell -= 11;
	}
	return CellPosition(vcell, hcell);
}
// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell
void CellPosition::AddCellNum(int addedNum, Direction direction)
{
	int currentcellnum = GetCellNum();

	if (currentcellnum == -1)
		return;

	int newCellNum = currentcellnum;
	if (direction == UP)
	{
		newCellNum += addedNum * 11;
	}
	else if (direction == DOWN)
	{
		newCellNum -= addedNum * 11;
	}
	else if (direction == RIGHT)
	{
		newCellNum += addedNum;
	}
	else if (direction == LEFT)
	{
		newCellNum -= addedNum;
	}
	if (newCellNum >= 1 && newCellNum <= 55)
	{
		CellPosition newPosition = GetCellPositionFromNum(newCellNum);
		vCell = newPosition.VCell();
		hCell = newPosition.HCell();
	}
}