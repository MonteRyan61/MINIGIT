#include "miniGit.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <filesystem> //added from write up in order to create and delete directories

using namespace std;
namespace fs = std::filesystem;

git::git() //constructor deletes minigit directory if previously existing
{   
    fs::remove_all(".minigit");
}

git::~git() //destructor needed to free all memory at program's termination
{
    fs::remove_all(".minigit");
    doublyNode* curr = commitHead;
    doublyNode* next = NULL;
    singlyNode* scurr = NULL;
    singlyNode* snext = NULL;
    while(curr != NULL)
    {
        scurr = curr->head;
        while(scurr != NULL)
        {
            snext = scurr->next;
            delete scurr;
            scurr = snext;
        }
        next = curr->next;
        delete curr;
        curr = next;
    }
     if(currCommit != NULL)
    {
        scurr = currCommit->head;
        while(scurr != NULL)
        {
            snext = scurr->next;
            delete scurr;
            scurr = snext;
        }
        delete currCommit;
        currCommit = NULL;
    }

}

void git::initialize() // function that initalizes a new repo
 {
    fs::create_directory(".minigit"); // creates a new directory named ".minigit"
    currCommit = new doublyNode; // initializes a doubly node
    currCommit->commitNumber = 0;
    commitHead = NULL; // the singly node's head and tail point to current commit, which can be added to, and removed from, and committed
    commitTail = NULL;
 }

// --------------------------------------------------------------------------------------------------------------------------------------
// ADD FILES-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------

/*
This function iterates the version type. 
Variables: name: name of the file; check: if 1 then file is created, else the file needs to be created
*/
string versionHelper(string name, int check) // helper function that names the file version and increments the version if needed
{
    //getting the end of the string .txt, .hpp, or .cpp
    string end = name.substr(name.length()-4, name.length());
    name.erase(name.length()-4, name.length());
    string final;

    if (check == 1) // passed in as a parameter, means that file version will be incremented
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

void git::addFile() // function that adds files to the current commit
{
    bool check = false;
    string filename;
    do 
    {
        //prompt user for file name
        cout << "Please enter a valid file name: " << endl;
        getline(cin, filename);

        ifstream checkValidFilename(filename);

        if(!checkValidFilename.is_open()) // Check whether the file with the given name exists in the current directory.
        {
            cout << "Invalid file name! Try again." << endl;
        }
        else
        {
            check = true; /// file name exists in current directory
        }

    } while (check == false); // If not, keep prompting the user to enter a valid file name

    //Check current commit to see whether the file has already been added. File with same name can't be added twice
    singlyNode *curr = currCommit->head;
    singlyNode *prev = NULL;
    if(currCommit->head == NULL) //need to add this file to the head of the current commit
    {
        //cout << "ADD HEAD" << endl; //DEBUGGING
        singlyNode *add = new singlyNode;
        add->fileName = filename;
        add->fileVersion = versionHelper(filename, 0); 
        add->next = NULL;
        currCommit->head = add; //update the head pointer in curr to add
        return;
    }
    //if it the singly in the currCommit was not empty must make sure file with that name doesn't exist already and if it doesn't then go ahead and add if it does print that.
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
        singlyNode *add = new singlyNode;
        add->fileName = filename;
        add->fileVersion = versionHelper(filename, 0); 
        add->next = NULL;
        prev->next = add;
    }
    else //filename was found
    {
        cout << "File with that name already exists in the current commit" << endl;
        return;
    }
}

// --------------------------------------------------------------------------------------------------------------------------------------
// REMOVE FILES--------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------

bool git::removeFile(string filename) // function that removes files from the current commit
{
    //first must check if the file name exists in the singly linked list
    singlyNode *curr = currCommit->head; //wanna access which ever commit we are currently in's head in order to traverse it and see if the file exists in the current version of the repository
    singlyNode *prev = NULL; //prev set up to help with deletion if the node does exist
    //cout << filename << endl; //DEBUGGING
    while(curr != NULL) //may change to curr->next if seg fault
    {
        if(curr->fileName == filename) //its been found then we want to go ahead and delet it from the SLL
        {
            if(prev == NULL)//deleted the head of the SLL
            {
                currCommit->head = currCommit->head->next; //update the head of the current commit
                delete curr; //free the memory that was last located at that SLL node
                curr = NULL; //prevent seg faults
                return true; //the file has been removed from the commit
            }
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

// --------------------------------------------------------------------------------------------------------------------------------------
// COMMIT CHANGES------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------

bool _NotInDirectory(string &singlyFileVersion) // helper function, checks if file version exists in .minigit directory or not
{
    bool NotInDirectory = false;
    string temp = ".minigit/" + singlyFileVersion;
    ifstream findMe(temp);
    if(!findMe.is_open()) // if file version doesn't open in .minigit directory, then file version doesn't exist
    {
        //cout << "File version " << singlyFileVersion << " does not exist in .minigit directory." << endl; //DEBUGGING
        NotInDirectory = true;
    }
    findMe.close();

return NotInDirectory;
}

void _copyFiles(string fileVersion, int increment, string filename) // helper function to copy files into .minigit directory
{
    string addThis = fileVersion;
    //cout << "Will be copying this file into .minigit: " << addThis << endl; //DEBUGGING

    if(increment == 1) // file version is different
    {
        addThis = versionHelper(fileVersion, 1); // called upon helper function that increments version
    }

    string nowAdding = ".minigit/" + addThis;
    ifstream addThisFileVersion(filename); // created reading stream of file name
    ofstream nowAddingFileVersion(nowAdding); // created writing stream into .minigit directory
    char addThisFileC;

    // check for failures of opening reading and writing streams
    if(!addThisFileVersion.is_open())
    {
        cout << "File " << filename << " to be read failed to open." << endl;
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
    nowAddingFileVersion.close(); // close streams
}


void git::commitChanges() // pass in pointer to head of temporary singly list
{
    int mostRecentCommitNumber = 0;
    doublyNode* mostRecentCommit = commitTail; // always compare to most recent commit

    // if(commitTail != NULL)
    // {
    //     cout << "commitTail's commitNumber: " << commitTail->commitNumber << endl;
    // }
    singlyNode* tempSinglyRecentCommit;
    if(commitTail != NULL) //do not wanna try and access mostRecent if there is not most recent commit (like with first commit case)
    {
        mostRecentCommitNumber = mostRecentCommit->commitNumber; // get most recent commit number
        tempSinglyRecentCommit = mostRecentCommit->head; // traverse through most recent commit's SLL
    }
    singlyNode* tempSinglyListTrav = currCommit->head; // traverse through temporary SLL in currentCommit (with nodes that are to be added/have been modified)

    while(tempSinglyListTrav != NULL) // traverse through temporary SLL
    {
        if(_NotInDirectory(tempSinglyListTrav->fileVersion) == true) // if file version does not currently exist in .minigit directory
        {
            //cout << "DON'T EXIST" << endl;
            _copyFiles(tempSinglyListTrav->fileVersion, 0, tempSinglyListTrav->fileName); // call upon helper function, pass in a 0 means that file version won't be incremented
        }
        else if(_NotInDirectory(tempSinglyListTrav->fileVersion) == false) // file version does currently exist in .minigit directory
        {
            //cout << "FILE EXISTS" << endl;
            bool isChanged = false;
            doublyNode* iterate = commitTail;
            singlyNode* singleIterate =  NULL;
            string currentVersion;
            bool oldversionfound = false;
            while(iterate != NULL && oldversionfound == false)
            {
                singleIterate = iterate->head;
                while(singleIterate != NULL)
                {
                    if(singleIterate->fileName == tempSinglyListTrav->fileName)
                    {
                       currentVersion = singleIterate->fileVersion;
                       oldversionfound = true;
                       break;
                    }
                    singleIterate = singleIterate->next;
                }
                iterate = iterate->previous;
            }
            string gitVersion = ".minigit/" + currentVersion;
            //cout << gitVersion << endl;
            ifstream CurrentFileVersion(tempSinglyListTrav->fileName);
            ifstream gitFileVersion(gitVersion); // created reading streams of files

            char CurrentFileVersionC, gitFileVersionC;

            // check for failures of opening reading streams
            if(!CurrentFileVersion.is_open())
            {
                cout << "File " << tempSinglyListTrav->fileName << " to be read failed to open." << endl;
                break;
            }

            if(!gitFileVersion.is_open())
            {
                cout << "File " << gitVersion << " to also be read failed to open." << endl;
                break;
            }

            while(1) // read from both files, check if files are the same or not
            {
                CurrentFileVersionC = CurrentFileVersion.get();
                gitFileVersionC = gitFileVersion.get();

                if(CurrentFileVersionC != gitFileVersionC) // the moment that a character from both files don't match
                {
                    //cout << "Files are different." << endl;
                    isChanged = true;
                    break;
                }

                if(CurrentFileVersionC == EOF) // if the end of the file to be read is reached
                {
                    break;
                }
            }

            CurrentFileVersion.close();
            gitFileVersion.close(); // close streams

            if(isChanged == true) // if file versions are different
            {
                _copyFiles(currentVersion, 1, tempSinglyListTrav->fileName); // call upon helper function, pass in a 1, which means that version will be incremented
                tempSinglyListTrav->fileVersion = versionHelper(currentVersion, 1); // wanna update that version number as it has been modified
            }
            // else
            // {
            //     cout << "Files are the same." << endl;
            // }
        }

        tempSinglyListTrav = tempSinglyListTrav->next;
    }


    doublyNode * newCommit = new doublyNode; // create new doublyNode 
    newCommit->commitNumber = mostRecentCommitNumber + 1; //update its commit number
    newCommit->previous = mostRecentCommit;
    // newCommit->next = NULL; given in the .hpp file
    if(mostRecentCommit != NULL) //prevent seg fault
    {
        //cout << "second Commit" << endl;
        mostRecentCommit->next = newCommit; //keep it in the loop
        commitTail = newCommit; //now is the most recent commit
    }
    else // special case for very first commit
    {
        //cout << "FIRST COMMIT" << endl;
        commitHead = newCommit;
        commitTail = newCommit;
    }
    
    bool headfilled = false;
    singlyNode* previousInNew = NULL;
    singlyNode* traversecopy = currCommit->head;
    while(traversecopy != NULL) // copying curr commit's SLL to new commit's SLL
    {
        singlyNode* SinglyNodeNewCommit = new singlyNode; // create new singly node to be added to new commit
        SinglyNodeNewCommit->fileName = traversecopy->fileName; //copy the information over to the newcommit's SLL
        SinglyNodeNewCommit->fileVersion = traversecopy->fileVersion;
        if(headfilled == false) //must update the current commits head as first in singly
        {
            newCommit->head = SinglyNodeNewCommit;
            headfilled = true;
            //cout << "head" << endl;
        }
        else
        {
            //if not the head need to update the pointers
            //cout << "Not Head" << endl;
            previousInNew->next = SinglyNodeNewCommit;
            SinglyNodeNewCommit->next = NULL;
        }

        //continue to traverse currCommits singly
        previousInNew = SinglyNodeNewCommit;
        traversecopy = traversecopy->next;
    }

    // pretty print commit and file versions
    doublyNode* curr = commitHead;
    singlyNode* currsin = NULL;
    while(curr != NULL)
    {
        //cout << "Commit number: " << curr->commitNumber << endl;
        currsin = curr->head;
        while(currsin != NULL)
        {
            //cout << currsin->fileVersion << endl;
            currsin = currsin->next;
        }
        curr = curr->next;
    }

return;
}


// --------------------------------------------------------------------------------------------------------------------------------------
// CHECKOUT------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------


void _copyFiles_checkout(string fileVersion, string filename) // helper function to copy files into .minigit directory
{
    string addThisToDirectory = fileVersion;
    //cout << "copy" << endl;

    string nowAdding = ".minigit/" + addThisToDirectory;
    ifstream writeFrom(nowAdding); //writing from the .minigit
    ofstream writeToo(filename); //writing to the file name in the directory
    char addThisFileC;

    // check for failures of opening reading and writing streams
    if(!writeToo.is_open())
    {
        cout << "File " << filename << " to be read failed to open." << endl;
        return;
    }

    if(!writeFrom.is_open())
    {
        cout << "File " << nowAdding << " to write into failed to open." << endl;
        return;
    }

    while(writeFrom.get(addThisFileC)) // copying to .minigit directory
    {
        writeToo << addThisFileC;
    }

    writeToo.close();
    writeFrom.close(); // close streams
}


void git::checkout() // function that allows user to visit different commits
{
    int _commitNumber;
    string choice;
    cout << "Are you sure that you would like to check out a seperate commit?"
    " You will lose your local changes if you check out a different version before commiting your local changes" << endl;
    cout << "Enter Y to continue and N to not" << endl;
    getline(cin,choice);
    if(choice == "Y")
    {
        cout << "Which commit number would you like to check out" << endl;
        string x;
        getline(cin, x);
        _commitNumber = stoi(x);
    }
    else if(choice == "N")
    {
        return;
    }
    else // check for valid user input
    {
        cout << "Invalid Input" << endl;
        return;
    }

    doublyNode* curr = commitHead;
    //first wanna get curr on the node they wanna check out and make sure that that commit number is valid
    if(_commitNumber < 1 || _commitNumber > commitTail->commitNumber)
    { // no negative commits, no commit number 0 (since at commit number 0, file versions don't yet exist in .minigit), no commit number greater than current commit number
        cout << "Invalid commit number to check out with" << endl;
        return;
    }
    while(curr != NULL) // wanna traverse the list and get onto the commit the user would like to check out
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
    singlyNode* toreplacewith = curr->head; //want the singly list from the commit we want to check out with

    while(toreplacewith != NULL) // traverse through temporary SLL and copy to the directory whatever is stored in ther
    {
        _copyFiles_checkout(toreplacewith->fileVersion, toreplacewith->fileName); // call upon helper function, to copy from the .minigit to the current directory
        toreplacewith = toreplacewith->next;
    }
    string inp;
    bool correct = false;
    while(correct == false)
    {
        cout << "You are now view and old save in order to add, remove, and commit again Type Y to return to the most current commit" << endl;
        getline(cin, inp);
        if(inp == "Y")
        {
            correct = true;
        }
    }
    //want to now return them to the most recent commit viewing so they can make changes
    singlyNode* backto = commitTail->head; //want the singly list from the commit we want to check out with which is now the most recent commit to allow user to make changes again
    while(backto != NULL) // traverse through temporary SLL and copy to the directory whatever is stored in ther
    {
        _copyFiles_checkout(backto->fileVersion, backto->fileName); // call upon helper function, to copy from the .minigit to the current directory
        backto = backto->next;
    }
    //now will be back on most recent commit and can make changes again
    return;
}