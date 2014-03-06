//test_balanced_bst.cpp
//Iqbal:Arsum:A00351433:CSC34218
//Submission 09: Creating and Displaying Balanced Binary Search Trees

/*
UPDATE 1 @ 11:56 PM on 3/10/2013 : Started Program
UPDATE 2 @ 6:57 PM on 3/17/2013 : Only Displaying BST left
UPDATE 3 @ 8:05 PM on 3/17/2013 : Program finished but i couldn't get it
to draw the tree... it does however print out the tree in level order
traversal , just couldnt draw the \ and / ... :(
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

#include "utilities.h"
#include "balanced_bst.h"

using Scobey::DisplayOpeningScreen;
using Scobey::Pause;
using Scobey::Menu;
using Scobey::RandomGenerator;

void AddMenuOptions
    (
    Menu& m //in out
    );

/**<
Builds the required menu by adding the necessary options.
*/

int main()
{
    DisplayOpeningScreen("Iqbal:Arsum:A00351433:CSC34218",
        "Creating and Displaying Balanced Binary Search Trees");
    vector<char> treeValues;
    RandomGenerator randomValues;
    TreeNode node;
    int count = 0;
    int height = 0;
    bool success = false;
    Menu m("Menu for Balanced Character BST Creation and Display");
    AddMenuOptions(m);
    int menuChoice;
    do
    {
        m.display();
        menuChoice = m.getChoice();
        switch (menuChoice)
        {
        case 1: case -1:
            break;
        case 2:
            cout << "Enter characters into the vector (terminate with an end"
                "-of-file on a new line): ";
            //clears previous values in the vector
            treeValues.clear();
            char values;
            while(cin >> values)
                //store characters into vector
                treeValues.push_back(values);
            //clear input stream
            cin.clear();
            Pause(0, "All characters have been entered into the vector.");
            //set success to false because bst hasnt been created yet
            success = false;
            break;
        case 3:
            int requiredVal;
            cout << "Enter required number of values: ";
            cin >> requiredVal;
            char firstVal;
            cout << "Enter first value of character range: ";
            cin >> firstVal;
            char secondVal;
            cout << "Enter last value of character range: ";
            cin >> secondVal;
            //clear previous value of vector
            treeValues.clear();
            while(count != requiredVal)
            {
                //get a random string from given character range
                string temp = randomValues.getNextStringFromCharRange
                    (1,firstVal,secondVal);
                //convert to a character
                const char* generatedVal = temp.c_str();
                vector<char>::iterator p1 = treeValues.begin();
                //find the character in the vector
                p1 = find(treeValues.begin(),treeValues.end(),*generatedVal);
                //if it couldnt find the value
                if(p1 == treeValues.end())
                {
                    //insert the value into the vector
                    treeValues.push_back(*generatedVal);
                    count++;
                }
            }
            //reset counter
            count = 0;
            //clear input stream
            cin.ignore();
            Pause(0, "All values have been generated.");
            //set success to false because bst hasnt been created yet
            success = false;
            break;
        case 4:
            cout << "\nHere are the current contents of the vector:\n" << endl;
            //Display values from the vector
            copy(treeValues.begin(),treeValues.end(),
                ostream_iterator<char>(cout, " "));
            Pause(0, "\n");
            break;
        case 5:
            //create the binary search tree
            createBst(treeValues,node);
            Pause(0, "The balanced binary search tree has been created.");
            //set success to true because bst has been created
            success = true;
            break;
        case 6:
            //if the bst wasnt created
            if(!success)
            {
                cout << "Tree is empty. Nothing to display.\n";
                Pause();
                break;
            }
            //find the height of the bst
            height = findHeight(&node);
            if (height <= 3)
                displayTree(&node);
            else
                cout << "\nHeight of tree is too great for display (>=4).\n";
            Pause();
            break;
        }
    }
    while (menuChoice != 1 && menuChoice != -1);
    Pause(0, "Program now terminating.");
}

void AddMenuOptions
(
    Menu& m //inout
)
{
    m.addOption("Quit");
    m.addOption("Enter a vector of <= 15 unique values from the keyboard");
    m.addOption("Generate a vector of <= 15 unique random values");
    m.addOption("Display the vector of values");
    m.addOption("Put the vector of values into a balanced BST");
    m.addOption("Display the tree if its height is <= 3 (which it should be)");
}