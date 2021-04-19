#include "miniGit.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem> //added from write up in order to create and delete directories

using namespace std;
namespace fs = std::filesystem;
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


bool git::removeFile(string filename, doublyNode* tmp)
{
    //first must check if the file name exists in the singly linked list
    singlyNode *curr = tmp->head; //wanna access which ever commit we are currently in's head in order to traverse it and see if the file exists in the current version of the repository
    singlyNode *prev = NULL; //prev set up to help with deletion if the node does exist
    cout << curr->fileName << endl;
    cout << filename << endl;
    if(tmp->head->fileName == filename)//deleted the head of the SLL
            {
                cout << "deleted" << endl;
                tmp->head = curr->next; //update the head of the current commit
                delete curr; //free the memory that was last located at that SLL node
                curr = NULL; //prevent seg faults
                return true; //the file has been removed from the commit
            }
    while(curr != NULL) //may change to curr->next if seg fault
    {
        if(curr->fileName == filename) //its been found then we want to go ahead and delet it from the SLL
        {
                cout << "ELSE" << endl;
                prev->next = curr->next; //skip over the file to be deleted in the linked list
                delete curr;
                curr = NULL;
                return true; //the file has been removed from the SLL
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

return pointerToRecentCommit; // return a pointer to the most recent commit
}


bool _NotInDirectory(string &singlyFileVersion) // helper function, checks if file version exists in .minigit directory or not
{
    bool NotInDirectory = false;
    string temp = ".minigit/" + singlyFileVersion;
    ifstream findMe(temp);
    if(!findMe.is_open()) // if file version doesn't open in .minigit directory, then file version doesn't exist
    {
        cout << "File version " << singlyFileVersion << " does not exist in .minigit directory." << endl;
        NotInDirectory = true;
    }
    findMe.close();

return NotInDirectory;
}


void _copyFiles(string fileVersion, int increment) // helper function to copy files into .minigit directory
{
    string addThis = fileVersion; // not always a txt file!

    if(increment == 1) // file version is different
    {
        addThis = versionHelper(fileVersion, 1); // called upon helper function that increments version
    }

    string nowAdding = ".minigit/" + addThis;
    ifstream addThisFileVersion(addThis);
    ofstream nowAddingFileVersion(nowAdding);

    char addThisFileC;

    if(!addThisFileVersion.is_open())
    {
        cout << "File " << addThis << " to be read failed to open." << endl;
        return;
    }

    if(!nowAddingFileVersion.is_open())
    {
        cout << "File " << nowAdding << " to write into failed to open." << endl;
        return;
    }

    while(addThisFileVersion.get(addThisFileC)) // copying to .minigit directory
    {
        nowAddingFileVersion << addThisFileC;
    }

    addThisFileVersion.close();
    nowAddingFileVersion.close();
}


bool git::commitChanges(singlyNode* _sll) // pass in pointer to head of temporary singly list
{
    bool isCommitted = false;
    doublyNode* mostRecentCommit = _findMostRecentCommit(commitHead); // always compare to most recent commit
    int mostRecentCommitNumber = mostRecentCommit->commitNumber; // get most recent commit number

    singlyNode* tempSinglyList = _sll; // traverse through temporary SLL (with nodes that are to be added/have been modified)
    singlyNode* tempSinglyRecentCommit = mostRecentCommit->head; // traverse through most recent commit's SLL


    while(_sll != NULL) // traverse through temporary SLL
    {
        if(_NotInDirectory(_sll->fileVersion) == true) // if file version does not currently exist in .minigit directory
        {
            _copyFiles(_sll->fileVersion, 0); // call upon helper function, pass in a 0 means that file version won't be incremented
        }

        if(_NotInDirectory(_sll->fileVersion) == false) // file version does currently exist in .minigit directory
        {
            bool isChanged = false;

            string currentVersion = _sll->fileVersion; // not always a txt file!
            string gitVersion = ".minigit/" + currentVersion;
            ifstream CurrentFileVersion(_sll->fileVersion);
            ifstream gitFileVersion(gitVersion);

            char CurrentFileVersionC, gitFileVersionC;

            if(!CurrentFileVersion.is_open())
            {
                cout << "File " << currentVersion << " to be read failed to open." << endl;
                break;
            }

            if(!gitFileVersion.is_open())
            {
                cout << "File " << gitVersion << " to write into failed to open." << endl;
                break;
            }

            while(1) // read from both files, check if files are the same or not
            {
                CurrentFileVersionC = CurrentFileVersion.get();
                gitFileVersionC = gitFileVersion.get();

                if(CurrentFileVersionC != gitFileVersionC)
                {
                    cout << "Files are different." << endl;
                    isChanged = true;
                    break;
                }

                if(CurrentFileVersionC == EOF)
                {
                    break;
                }
            }

            if(isChanged == true) // if file versions are different
            {
                _copyFiles(_sll->fileVersion, 1); // call upon helper function, pass in a 1, which means that version will be incremented
            }

            cout << "Files are the same." << endl;
        }
        _sll = _sll->next;
    }

    doublyNode * newCommit = new doublyNode; // create new doublyNode
    newCommit->commitNumber = mostRecentCommit->commitNumber + 1;
    newCommit->previous = mostRecentCommit;
    mostRecentCommit->next = newCommit;
    // newCommit->next = NULL; given in the .hpp file

    // special case for very first commit?

    singlyNode* currSinglyNewCommit = newCommit->head; // pointer to traverse through new commit's SLL

    while(tempSinglyRecentCommit != NULL) // copying most recent commit's SLL to new commit's SLL
    {
        singlyNode* SinglyNodeNewCommit = new singlyNode; // create new singly node to be added to new commit
        SinglyNodeNewCommit->fileName = tempSinglyRecentCommit->fileName;
        SinglyNodeNewCommit->fileVersion = tempSinglyRecentCommit->fileVersion;

        currSinglyNewCommit = SinglyNodeNewCommit;

        tempSinglyRecentCommit = tempSinglyRecentCommit->next;
        currSinglyNewCommit = currSinglyNewCommit->next;
    }



            // add new singly node, with version number that didn't previously exist, to end of newCommit SLL
// cout << headCommit->commitNumber << endl;

return isCommitted;
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

git::git() //constructor will create the .minigit folder
{   
    fs::remove_all(".minigit");
}
 void git::initialize()
 {
    fs::create_directory(".minigit");
 }