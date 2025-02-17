#include "Workshop.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

Workshop::Workshop(const CellPosition& workshopPosition) :GameObject(workshopPosition), repairAmount(0)
{

}


void Workshop::Draw(Output* pOut) const
{
    pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, Player* pPlayer)
{
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;

    // Print workshop message
    pOut->PrintMessage("Welcome to the Workshop! Choose from to buy: 1. Double Laser 2. Extended Memory 3. Toolkit 4. Hack Device 5. Laser Reflect Gear 6. Shield.7.rnp");
    string choice = pIn->GetSrting(pOut);

    if (choice == "1") {
        // Player chooses Double Laser
        if (!pPlayer->HasDoubleLaser()) { // Check if player already has Double Laser
            pPlayer->EquipDoubleLaser(); // Equip the player with a double laser
            pOut->PrintMessage("You have equipped a Double Laser! Click anywhere to continue...");
        }
        else {
            pOut->PrintMessage("You already have a Double Laser. Click anywhere to continue...");
        }
    }
    else if (choice == "2") {
        // Player chooses Extended Memory
        if (!pPlayer->HasExtendedMemory()) { // Check if player already has Extended Memory
            pPlayer->EnableExtendedMemory(); // Enable extended memory
            pOut->PrintMessage("You now have Extended Memory! Click anywhere to continue...");
        }
        else {
            pOut->PrintMessage("You already have Extended Memory. Click anywhere to continue...");
        }
    }
    else if (choice == "3") {
        // Player chooses Toolkit
        if (!pPlayer->HasToolkit()) { // Check if player already has a Toolkit
            pPlayer->AddToolkit(); // Add a toolkit to the player
            pOut->PrintMessage("You have acquired a Toolkit! Click anywhere to continue...");
        }
        else {
            pOut->PrintMessage("You already have a Toolkit. Click anywhere to continue...");
        }
    }
    else if (choice == "4") {
        // Player chooses Hack Device
        if (!pPlayer->HasHackDevice()) { // Check if player already has a Hack Device
            pPlayer->AddHackDevice(); // Add a hack device to the player
            pOut->PrintMessage("You have acquired a Hack Device! Click anywhere to continue...");
        }
        else {
            pOut->PrintMessage("You already have a Hack Device. Click anywhere to continue...");
        }
    }
    else if (choice == "5") {
        // Player chooses Laser Reflect Gear
        if (!pPlayer->HasLaserReflection()) { // Check if player already has Laser Reflect Gear
            pPlayer->EnableLaserReflection(); // Equip the player with Laser Reflect Gear
            pOut->PrintMessage("You have acquired Laser Reflect Gear! Click anywhere to continue...");
        }
        else {
            pOut->PrintMessage("You already have Laser Reflect Gear. Click anywhere to continue...");
        }
    }
    else if (choice == "6") {
        // Player chooses Shield Mechanism
        if (!pPlayer->HasShield()) { // Check if player already has a Shield
            pPlayer->EnableShield(); // Equip the player with a shield
            pOut->PrintMessage("You have acquired a Shield! Click anywhere to continue...");
        }
        else {
            pOut->PrintMessage("You already have a Shield. Click anywhere to continue...");
        }
    }
    else if (choice == "7") {
        // Player chooses Shield Mechanism
        if (!pPlayer->HasRebootnRepair()) { // Check if player already has a Shield
            pPlayer->setRebootnRepair(true); // Equip the player with a shield
            pOut->PrintMessage("You will be rebooted and repaired next round! Click anywhere to continue...");
        }
        else {
            pOut->PrintMessage("You already have a reboot and repair chance. Click anywhere to continue...");
        }
    }
    else {
        // Invalid choice
        pOut->PrintMessage("Invalid choice. Click anywhere to continue...");
    }


    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();
}
void Workshop::Save(ofstream& OutFile, int Type)
{
    if (Type == GetType()) { //  5 represents Workshops is saved fifth
        OutFile << position.GetCellNum() << " " << repairAmount << endl;
    }
}

void Workshop::Load(ifstream& InFile)
{
    int cellNum, repairAmount;
    InFile >> cellNum>>repairAmount;
    position = CellPosition::GetCellPositionFromNum(cellNum);
   
}
GameObject* Workshop::Copy() const
{
    return new Workshop(*this); // Use the copy constructor
}
Workshop::Workshop() : GameObject(CellPosition()), repairAmount(0) {
    // Initialize with default CellPosition and repair amount
}
Workshop::Workshop(const CellPosition& pos, int repairAmt) : GameObject(pos), repairAmount(repairAmt) {
    // Initialization code
}
int Workshop::GetType() const
{
    return 5;
}


Workshop::~Workshop()
{
}
