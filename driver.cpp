#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "miniGit.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    int opt = 0;
    git mainRepo;

    while(opt != 5) {
        string s;
        getline(cin, s);
        opt = stoi(s);

        switch(opt) {
            case 1:
            {
              //inialize directory 
              mkdir("hey.txt", 0777); //returns -1 if the dir isn't created
              doublyNode* headCommit = new doublyNode;
              headCommit->commitNumber = 0;
            }
            case 2: {
                //add files
                
                break;
            }

            case 3: {
                //removing files from the commit
                bool found = false;
                string toRemove;
                cout << "What is the name of the file that you would like to remove from the commit" << endl;
                do
                {
                    cout << "What is the name of the file that you would like to remove from the commit" << endl;
                    string toRemove;
                    getline(cin, toRemove);
                    if(toRemove == "quit") //check if they would like to leave the remove option
                    {
                        cout << "Leaving the remove nothing will be removed from the repository" << endl;
                        break;
                    }
                    found = mainRepo.removeFile(toRemove); //removeFile will return true if the file name was found and the string name was removed from the list
                    if(found == false)
                    {
                        cout << "That file does not exist in the current version of the repository please enter another or type quit if you would like to exit remove" << endl;
                    }
                } while (found == false);
                

                break;
            }

            case 4: {
                //commit changes
                break;
            }

            case 5: {
                //check out
                string choice;
                int comnum;
                cout << "Are you sure that you would like to check out a seperate commit you will lose your local changes if you check out a different version before commiting your local changes" << endl;
                cout << "Enter Y to conitue or N to not" << endl;
                cin >> choice;
                if(choice == "Y")
                {
                    cout << "Which commit number would you like to check out" << endl;
                    cin >> comnum;
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

