#include "miniGit.hpp"
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

bool git::removeFile(string filename)
{
    //first must check if the file name exists in the singly linked list
    singlyNode *curr = commitHead->head; //wanna access which ever commit we are currently in's head in order to traverse it and see if the file exists in the current version of the repository
    singlyNode *prev = NULL; //prev set up to help with deletion if the node does exist
    while(curr != NULL) //may change to curr->next if seg fault
    {
        if(curr->fileName == filename) //its been found then we want to go ahead and delet it from the SLL
        {
            if(curr == commitHead->head)//deleted the head of the SLL
            {
                commitHead->head = curr->next; //update the head of the current commit
                delete curr; //free the memory that was last located at that SLL node
                curr = NULL; //prevent seg faults
                return true; //the file has been removed from the commit
            }
            else //deleted from somewhere else in the SLL not the head
            {
                prev->next = curr->next; //skip over the file to be deleted in the linked list
                delete curr;
                curr = NULL;
                return true; //the file has been removed from the SLL
            }
        }
        prev = curr;
        curr = curr->next;

    }
    //if the loop has exited without returning that means the string name did not match any nodes string name in the SLL so we return false and prompt the user to enter another name
    return false;
}

doublyNode* _findMostRecentCommit(doublyNode* &doublyHead) // helper function, always compare to most recent commit
{
    doublyNode* pointerToRecentCommit = doublyHead;
    while(pointerToRecentCommit->next != NULL)
    {
        pointerToRecentCommit = pointerToRecentCommit->next;
    }

return pointerToRecentCommit;
}

bool _NotInDirectory(string singlyFileVersion)
{
    bool NotInDirectory = false;
    string temp = ".minigit/" + singlyFileVersion;
    ifstream findMe(temp);
    if(!findMe.is_open())
    {
        cout << "File Version does not exist in .minigit directory." << endl;
        NotInDirectory = true;
    }
    findMe.close();

return NotInDirectory;
}

bool git::commitChanges()
{
    bool isCommitted = false;
    doublyNode* mostRecentCommit = _findMostRecentCommit(commitHead); // always compare to most recent commit
    int mostRecentCommitNumber = mostRecentCommit->commitNumber;

    singlyNode* temp = mostRecentCommit->head;

    while(temp != NULL) // traverse through SLL of mostRecentCommit
    {
        if(_NotInDirectory(temp->fileVersion) == true) // fileVersion does not currently exist in .minigit directory
        {
            string nowAdding = "temporaryName.txt"; // not always a txt file!
            ifstream addThisFileVersion(temp->fileVersion);
            ofstream nowAddingFileVersion(".minigit/" + temp->fileVersion);

            // string Methis = "holder.txt";
            // string temp = "test/" + Methis;
            // ifstream addThisFileVersion(Methis);
            // ofstream nowAddingFileVersion(temp);

            // char addFileC, nowAddingC;

            // if(!addThisFileVersion.is_open())
            // {
            //     cout << "File " << Methis << " failed to open." << endl;
            //     return 0;
            // }

            // while(addThisFileVersion.get(addFileC))
            // {
            //     nowAddingFileVersion << addFileC;
            // }

            // addThisFileVersion.close();
            // nowAddingFileVersion.close();
        }
    }
// cout << headCommit->commitNumber << endl;

return isCommitted;
}

void checkout(int _commitNumber)
{
    
}