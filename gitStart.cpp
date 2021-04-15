#include "gitStart.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void git::addFile(string filename)
{
    ifstream inFile;
    inFile.open(filename);
    //if (inFile.error()) //if it doesn't open
    {
        cout << "file failed to open" << endl;
    }
}

void git::removeFile(string filename)
{
    
}

void git::commitChanges()
{
// cout << headCommit->commitNumber << endl;
}

void checkout(int _commitNumber)
{
    
}