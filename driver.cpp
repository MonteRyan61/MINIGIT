#include <iostream>
#include <fstream>
#include <string>
#include "miniGit.hpp"

using namespace std;

void menu()
{
    cout << "---- MENU ----" << endl;
    cout << "1. Add files to the current commit" << endl;
    cout << "2. Remove files from the current commit" << endl;
    cout << "3. Commit the changes" << endl;
    cout << "4. Check out a specific version based on a unique commit number" << endl;
    cout << "5. Quit" << endl;
}

int main(int argc, char* argv[])
{
    int opt = 0;
    int numCommits = 0;
    git mainRepo; //establishing the class git
    bool initialized = false;
    string initialChoice;
    //only want the repository to be initialized once so can do that here
    while (initialized == false)
    {
        cout << "Would you like to initialize a new repository?" << endl;
        cout << "Enter Y or N" << endl;
        getline(cin, initialChoice);
        if(initialChoice == "Y") //if yes then the .minigit directory will be created
        {
            mainRepo.initialize();
            initialized = true;
        }
        else if(initialChoice == "N") //if no they will exit they have no use for the .minigit if they do not want to create a repository
        {
            cout << "Quitting..." << endl;
            exit(0);
        }
        else
        {
            cout << "Invalid option please enter Y to create a new repository and N to exit minigit" << endl;
        }
    }

    while(opt != 5) {
        cout << endl << endl; // view menu easier in terminal
        menu(); //printing menu

        //getting user input
        string s;
        getline(cin, s);

        while(int(s[0]) > 53 || int(s[0]) < 49) // check to make sure user inputs number 1 through 5
        {
            cout << "Invalid input, please select a valid menu option." << endl << endl;
            menu();
            getline(cin, s);
        }

        opt = stoi(s);
        
        switch(opt) {
            //add files
            case 1: {
                //add files
                mainRepo.addFile();
                break;
            }
            //removing files from the commit        
            case 2: {
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
                    found = mainRepo.removeFile(toRemove); //removeFile will return true if the file name was found and the string name was removed from the list
                    if(found == false)
                    {
                        cout << "That file does not exist in the current version of the repository, "
                            << "please enter another or type quit if you would like to exit remove" << endl;
                    }
                } while (found == false);
                break;
            }

            //commit changes
            case 3: {
                string answer;
                bool acceptableAnswer = false; // return true if user inputted "yes" or "no"

                while(acceptableAnswer == false)
                {
                    cout << "Are you sure you'd like to commit your files? Enter Y or N" << endl;
                    getline(cin, answer);
                    if(answer == "Y") // if yes then call upon commit changes function
                    {
                        acceptableAnswer = true;
                        mainRepo.commitChanges();
                    }
                    else if(answer == "N") //if no then leave commit changes option
                    {
                        acceptableAnswer = true;
                        cout << "Will not commit files." << endl;
                    }
                    else // if user inputted something besides "yes" or "no"
                    {
                        cout << "Invalid option, please enter Y to commit changes." << endl;
                    }
                }

                break;
            }

            //check out
            case 4: {
                string choice;
                int comnum;
                mainRepo.checkout();
                break;
            }

            case 5: {
                cout << "Quitting..." << endl;
                //add warning about losing files
                break;
            }
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
