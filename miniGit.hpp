#pragma once

#ifndef GIT_H
#define GIT_H
#include<iostream>

using namespace std;

struct singlyNode
{
    string fileName;   // Name of local file, input file name
    string fileVersion; // Name of file in .minigit foldersinglyNode * next; repository name
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
        void addFile(singlyNode *sll); // user prompted to pass in file name to be added
        bool removeFile(string _filename2, doublyNode* tmp); // user prompted to pass in file name to be removed
        bool commitChanges(singlyNode *_sll); // 
        void checkout(int _commitNumber); // user prompted for commit number, pass into this function
        // add boolean for checkout function, if true then disallow other functions?
        
        
    private:
    doublyNode* commitHead;
    doublyNode* commitTail;
};

#endif