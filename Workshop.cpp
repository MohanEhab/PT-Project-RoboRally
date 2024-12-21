#include "Workshop.h"



Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid * pGrid, Player * pPlayer)
{
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int x, y;

    // Print workshop message
    pOut->PrintMessage("Welcome to the Workshop! Choose what you want to buy: 1. Double Laser 2. Extended Memory 3. Toolkit 4. Hack Device. Type your choice and press Enter.");
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
    else {
        // Invalid choice
        pOut->PrintMessage("Invalid choice. Click anywhere to continue...");
    }

    // Wait for the player to click before clearing the message
    
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();
}

Workshop::~Workshop()
{
}
