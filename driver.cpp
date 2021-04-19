#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "miniGit.hpp"

using namespace std;

void menu()
{
    cout << "---- MENU ----" << endl;
    cout << "1. Create directory" << endl;
    cout << "2. Add files to the current commit" << endl;
    cout << "3. Remove files from the current commit" << endl;
    cout << "4. Commit the changes" << endl;
    cout << "5. Check out a specific version based on a unique commit number" << endl;
    cout << "6. Quit" << endl;
}

int main(int argc, char* argv[])
{
    int opt = 0;
    git mainRepo; //establishing the class git
    int numCommits = 0;

    //initializes a doubly node and the singly node's head point
    doublyNode* tmp = new doublyNode;
    tmp->commitNumber = numCommits; //not sure what to do with the commitNumbers
    singlyNode* head = new singlyNode;
    tmp->head = head;

    while(opt != 6) {
        menu(); //printing menu

        //getting user input
        string s;
        getline(cin, s);
        opt = stoi(s);
        
        switch(opt) {
            //intialize directory
            case 1: 
            {
                //creates a new directory
                mkdir(".minigit", 0777); //returns -1 if the dir isn't created
                doublyNode* headCommit = new doublyNode;
                headCommit->commitNumber = 0; 
                break;
            }
            //add files
            case 2: {
                //add files
                mainRepo.addFile(tmp->head);
                break;
            }
            //removing files from the commit        
            case 3: {
                bool found = false;
                string toRemove;
                //cout << "What is the name of the file that you would like to remove from the commit" << endl;
                do
                {
                    cout << "What is the name of the file that you would like to remove from the commit" << endl;
                    string toRemove;
                    getline(cin, toRemove);
                    if(toRemove == "quit") //check if they would like to leave the remove option
                    {
                        cout << "Leaving the remove. Nothing will be removed from the repository" << endl;
                        break;
                    }
                    found = mainRepo.removeFile(toRemove, tmp); //removeFile will return true if the file name was found and the string name was removed from the list
                    if(found == false)
                    {
                        cout << "That file does not exist in the current version of the repository, "
                            << "please enter another or type quit if you would like to exit remove" << endl;
                    }
                } while (found == false);
                break;
            }

            //commit changes
            case 4: {
                string answer;
                bool commitSuccess = false; // return true if commit function was successful
                bool acceptableAnswer = false; // return true if user inputted "yes" or "no"

                do
                {
                    cout << "Are you sure you'd like to commit your files? (Yes/No)" << endl; // ask user if they're sure they'd like to commit
                    getline(cin,answer);

                    for(int i = 0; i < answer.size(); i++) // convert the user's input to lowercase letters
                    {
                        if(isupper(answer[i]))
                        {
                            answer[i] = tolower(answer[i]);
                        }
                    }

                    if(answer == "no") // if user would not like to commit
                    {
                        acceptableAnswer = true;
                        cout << "Will not commit files." << endl;
                    }

                    if(answer == "yes") // if user would like to commit
                    {
                        acceptableAnswer = true;
                        commitSuccess = mainRepo.commitChanges(tmp->head); // call upon commit function

                        if(commitSuccess == true) // if commit was successful
                        {
                            cout << "Commit Successful!" << endl;
                        }
                        else // if commit was not successful
                        {
                            cout << "Commit Failed." << endl;
                        }
                    }

                } while (acceptableAnswer == false); // if user inputted something besides "yes" or "no"

                break;
            }

            //check out
            case 5: {
                string choice;
                int comnum;
                cout << "Are you sure that you would like to check out a seperate commit?"
                    " You will lose your local changes if you check out a different version before commiting your local changes" << endl;
                cout << "Enter Y to continue and N to not" << endl;
                getline(cin,choice);
                if(choice == "Y")
                {
                    cout << "Which commit number would you like to check out" << endl;
                    string x;
                    getline(cin, x);
                    comnum = stoi(x);

                    mainRepo.checkout(comnum);
                }
                break;
            }

            case 6: {
                cout << "Quitting..." << endl;
                //add warning about losing files
                break;
            }

        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}

