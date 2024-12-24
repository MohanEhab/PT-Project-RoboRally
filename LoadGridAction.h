#pragma once
#include "Action.h"
#include <fstream>
using namespace std;

class LoadGridAction : public Action {
private:
    string fileName; //  to load the grid from
public:
    LoadGridAction(ApplicationManager* pApp); // Constructor
    virtual void ReadActionParameters();      // Reads the file name
    virtual void Execute();                   // Executes the load operation
};

