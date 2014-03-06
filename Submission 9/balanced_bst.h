//balanced_bst.h
//Iqbal:Arsum:A00351433:CSC34218
//Submission 09: Creating and Displaying Balanced Binary Search Trees

#include <vector>

struct TreeNode
{
    TreeNode* leftPtr;
    char      data;
    TreeNode* rightPtr;
};

void createBst
    (
    vector<char> valueVec, //in
    TreeNode& node //inout
    );

/**<
Creates a binary search tree
@param valueVec, the vector that contains the characters
@param node, the binary search tree that will contain the characters
@pre valueVvec and node have been declared and exist
@post successfully stores the characters into the binary search tree
*/

void displayTree
    (
    TreeNode* node //in
    );

/**<
Displays the binary search treee
@param node , the bst that already contains the characters
@pre node has its characters already in it
@post draws the binary search tree to the standard output
*/

int findHeight
    (
    TreeNode* node //in
    );

/**<
Finds the height of the binary search tree
@param node contains the characters 
@pre node has been loaded with its characters
@post returns an int that tells the height of the binary search tree
*/