#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gitStart.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    int opt = 0;


    while(opt != 5) {
        string s;
        getline(cin, s);
        opt = stoi(s);

        switch(opt) {
            case 1:
            {
              //inialize directory 
              mkdir("hey.txt", 0777); //returns -1 if the dir isn't created
              git mainRepo;
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
                    string toRemove;
                    getline(cin, toRemove);
                    found = mainRepo.removeFile(toRemove); //removeFile will return true if the file name was found and the string name was removed from the list
                } while (found == false);
                

                break;
            }

            case 4: {
                //commit changes
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

