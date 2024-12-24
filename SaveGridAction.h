#pragma once

#include "Action.h"
#include <string>
#include <fstream>
using namespace std;

class SaveGridAction : public Action {
private:
    string fileName; // name of the file to save the grid
public:
    SaveGridAction(ApplicationManager* pApp); // Constructor

    virtual void ReadActionParameters(); // Reads parameters (e.g., file name)
    virtual void Execute();              // Executes the save action
};
