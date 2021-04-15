#pragma once

#ifndef GIT_H
#define GIT_H
#include<iostream>

using namespace std;

struct singlyNode
{
    string fileName;   // Name of local file
    string fileVersion; // Name of file in .minigit foldersinglyNode * next;
    singlyNode * next = NULL;
};

struct doublyNode
{
    int commitNumber;
    singlyNode * head = NULL;
    doublyNode * previous = NULL;
    doublyNode * next = NULL;
};

class git
{
    public:
        void addFile(string _filename1); // user prompted to pass in file name to be added
        void removeFile(string _filename2); // user prompted to pass in file name to be removed
        void commitChanges(); // 
        void checkout(int _commitNumber); // user prompted for commit number, pass into this function
        // add boolean for checkout function, if true then disallow other functions?
        
        
    private:
};

#endif