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
              mkdir(".minigit", 0777); //returns -1 if the dir isn't created
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
                        commitSuccess = mainRepo.commitChanges(); // call upon commit function

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

            case 5: {
                //check out
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

