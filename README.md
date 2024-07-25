# Quest_List_Manager
A C++ file containing many functions that simulate creating, maintaining, and editing quest lines similar to that of a video game. It includes adding, modifying, and organizing quests, as well as features for managing quest-related data. Quests have atributes of name, exp, and position. It uses a linked list as the main data structure.
Sample cases are included.
# Installation
Steps for installation on a mac terminal

A. Ensure g++ is installed
  - brew install gcc

1. Clone the repo
  - https://github.com/KOsanesome/Quest_List_Manager.git
2. Go to directory
  - cd Quest_List_Manager
3. Compile the project file
  - g++ QuestListMng.cpp -o QuestListMng
4. Run it
  - ./QuestListMng

Steps for installing it on PC

A. Install a C++ compiler, such as MinGW

1. Clone the repo
  - https://github.com/KOsanesome/Quest_List_Manager.git
2. Go to directory
  - cd Quest_List_Manager
3. Compile the project file
  - g++ QuestListMng.cpp -o QuestListMng.exe
4. Run it
  - QuestListMng.exe

# Contributions
Comments, suggestions, and ideas are appreciated! If you're interested in contributing, please follow these steps:
1. Fork the project
2. Create a branch
  - git checkout -b feature-or-idea
3. Commit the changes
  - git commit -m "Description of changes"
4. Push the branch
  - git push origin feature-or-idea
5. Open a pull request

# Key Features
- nodeFunctions class
  - Functions that adds quest node to the start or the end of the list
  - Can inserts node in the middle of the list, position must be specified
- Searching class
  - Functions that will find the node that meets the specified criteria such as name, exp, or position
  - 2 functions that return the node with the highest or lowest exp
- Deletion class
  - Can erase nodes based on their name or position
  - 2 functions that erase the first or last node
- Sorting class: has functions that sort by name, exp, or original position (default)
- QuestLineCommands class
  - Functions that save, restore, or delete entire questlines
  - Can merge 2 questlines into one new line
  - Can copy or reverse an existing questline
- General functions:
  - Displays the current questline in full
  - Swap nodes around or get the number of nodes in a line
  - Alter node data

# Usage
This can be used in RPG type video games built in the C++ language. Viewing, adding, altering, or deleting quest are all simple actions that can be done with this file. The code allows users to integrate it into their projects or modify it to fit their specific requirements. Functions are provided to search for quests by various criteria, sort quests, and manage entire quest lines. Sample cases are included in the file to demonstrate how to use these functions effectively.
