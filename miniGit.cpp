#include "miniGit.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
/*
This function iterates the version type. 
Variables: 
    name: name of the file,    
    check: if 1 then file is created, else the file needs to be created
*/
string versionHelper(string name, int check)
{
    //getting the end of the string .txt, .hpp, or .cpp
    string end = name.substr(name.length()-4, name.length());
    name.erase(name.length()-4, name.length());
    string final;

    if (check == 1)
    {
        //getting the iteration of the file
        string num = name.substr(name.length()-2, name.length());
        name.erase(name.length()-2, name.length());
        
        //increasing the iteration and converting it back to a string
        int n = stoi(num);
        n++;
        stringstream ss;
        ss << setw(2) << setfill('0') << n;
        num = ss.str();
        
        //putting it all back together
        final = name + num + end;
    }

    else
    {
        final = name + "00" + end;
    }
    return final;
}

void git::addFile(singlyNode * sll)
{
    bool check = false;
    string filename;
    do 
    {
        //prompt user for file name
        cout << "Please enter a valid file name: " << endl;
        getline(cin, filename);

        //Check whether the file with the given name exists in the current directory.
        if (true)
        {
            check = true; //needs to be fixed
        }

    } while (check == false); //If not, keep prompting the user to enter a valid file name.
    
    //Check SLL whether the file has already been added. File with same name can't be added twice
    singlyNode *curr = sll;
    singlyNode *prev = NULL;
    while (curr != NULL)
    {
        if (filename == curr->fileName)
        {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    //filename was not found
    if (curr == NULL)
    {
        singlyNode *tmp = new singlyNode;
        tmp->fileName = filename;
        tmp->fileVersion = versionHelper(filename, 0); 
        tmp->next = NULL;
        prev->next = tmp;
    }
    else //filename was found
    {
        curr->fileVersion = versionHelper(filename, 1); 
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