#include "miniGit.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void git::addFile(string filename)
{
    //Check whether the file with the given name exists in the current directory.  
    
    //If not, keep prompting the user to enter a valid file name.
    //Check SLL whether the file has already been added. File with same name can't be added twice
    //A new SLL node gets added containing: name of input file, name of repository file, and next pointer
    //The repository file name should be the combination of the original file name and the version number.
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

void git::commitChanges()
{
// cout << headCommit->commitNumber << endl;
}

void git::checkout(int _commitNumber)
{
    doublyNode* curr = commitHead;
    //first wanna get curr on the node they wanna check out and make sure that that commit number is valid
    if(_commitNumber < 0) //will have no negative commits
    {
        cout << "Invalid commit number to check out with" << endl;
        return;
    }
    while(curr != NULL) //wanna traverse the list and get onto the commit the user would like to check out
    {   
        if(curr->commitNumber == _commitNumber)
        {
            break;
        }
        else
        {
            curr = curr->next;
        }
    }
    //now that curr is on the node the user would like to check out we must copy the files over from the repository to the user accesed files
    //implement a function in which will copy all files to the old string names in the hidden folder to the current directory
    //maybe use a helper function

}