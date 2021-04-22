# MINIGIT
Katherine, Sangati and Ryan will be creating and implementing our own version of git.

The program compiles with g++-std=c++17, and utilizes the filesystem library.

The core implementation of our version of git is as follows:

-----------------------------------------------------

Main menu:

A switch statement in a while loop that allows for the user to select between 5 options (add, remove, commit, checkout, or quit) when the program is run. 
The user is first prompted to initalize a new repository, where if they enter "Y" then a .minigit directory is created. The user can then choose from the above 5 options

(NOTE: upon initalization, commit number is at 0).

----------------------------------------------------

Add function (option 1):

The user can enter the name of the file they wish to add to the .minigit directory. 

(NOTE: file doesn't appear in .directory until committed). 

The program checks to make sure that the file they wish to add actually exists in the current directory. If an appropriate file name is entered,
then the user is taken back to the menu to make another choice, where they could add more files if desired.

(NOTE: names of the file versions of the files to be added all have "00" in it).

----------------------------------------------------

Remove function (option 2):

The user can enter the name of the file they wish to remove before committing to the .minigit directory. This applies to the files that a user
has added but decides not to commit -- those files can be removed with this function.

----------------------------------------------------

Commit function (option 3):

The user can choose to commit any added files or changes to files that they've previously added.
If the user is committing a file for the first time, te commit function checks to see if the file version (the name has "00" in it) already exists in the .minigit directory.
If not, then the file will be copied into the .minigit directory, and the following (sample) file version appears in the .minigit directory: "filename00.txt".

(NOTE: the user can add, remove, and commit .txt, .cpp, and .hpp files and the appropriate file types appear in the .minigit directory).

The commit function also checks to see if the files that the user has added has ever been modified. The function does this by comparing the (current version) file's contents
with the most recent commit's file's contents. If the user has made changes to the file, the commit function will detect that there has been a modification.
The contents of the (modified) file will be copied into the .minigit directory, where the file version will be incremented. 

Finally, with each new commit, a new doubly linked list node will be created, after all the files are scanned. A deep copy of the singly linked list from the previous commit
(the previous DLL node) will be copied into the new DLL. The commit number of the new DLL is equal to that of the previous DLL, incrememnted by one.

----------------------------------------------------

Checkout function (option 4):

The user can choose to checkout a previous commit. The user is warned that any changes that they've made to the curent version of their files will not be saved 
(if they haven't yet committed before checking out a previous committ). Once the user enters in a valid previous commit number, the files in their current version
in the current directory) will be overwritten with the file contents of the previous commit number. The user is not able to add, remove, or commit when checking out
a previous commit. Once the user is finished checking out, then they can enter "Y" to return back to the current version of their files in the current directory.

----------------------------------------------------

Quit (option 5):

The user can quit the program, and a message, "Goodbye!" notifies the user that the program has been terminated. A destructor in the .miniGit.cpp file then deallocates
all of the memory (that was allocated during the program's runtime to SLL, DLL nodes) in the .minigit directory. Finally, the .minigit directory is deleted as well.
