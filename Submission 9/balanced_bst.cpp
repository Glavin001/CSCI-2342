//balanced_bst.cpp
//Iqbal:Arsum:A00351433:CSC34218
//Submission 09: Creating and Displaying Balanced Binary Search Trees

#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

#include "balanced_bst.h"
#include "utilities.h"

using Scobey::isEven;

void createBst
    (
    vector<char> valueVec, //in
    TreeNode& node //inout
    )
{
    //if the size is 0 , just end
    if(valueVec.size() == 0)
        return;
    int middle = 0;
    //sort the vector
    sort(valueVec.begin(),valueVec.end());
    //if its even
    if(isEven(valueVec.size()))
        //set middle according to that calculation
        middle = ((valueVec.size())/2) - 1;
    else
        //set middle according to that calculation
        middle = valueVec.size()/2;
    //store the middle value into the .data of the node
    node.data = valueVec[middle];
    //create 2 subvectors, 1 for the left , 1 for the right
    vector<char> leftVec(valueVec.begin(),valueVec.begin()+ (middle));
    vector<char> rightVec(valueVec.begin() + (middle+1),valueVec.end());
    //if the size isnt 0
    if(leftVec.size() != 0)
        //create a new node
        node.leftPtr = new TreeNode;
    else
    {
        //set the pointers to null
        node.leftPtr = nullptr;
        node.rightPtr = nullptr;
    }
    //do recursion on the left side
    createBst(leftVec,*node.leftPtr);
    //if the size isnt 0
    if(rightVec.size() != 0)
        //create a new node
        node.rightPtr = new TreeNode;
    else
    {
        //set the pointers to null
        node.leftPtr = nullptr;
        node.rightPtr = nullptr;
    }
    //do recursion on the right side
    createBst(rightVec,*node.rightPtr);
}

void displayTree
    (
    TreeNode* node // in
    )
{
    queue<TreeNode*> temp;
    //if the root is valid
    if(node != nullptr)
        //push it to the queue
        temp.push(node);
    while(!temp.empty())
    {
        //make temp_node the front of the queue to use later
        const TreeNode* const temp_node = temp.front();
        //Remove the first item from the queue 
        temp.pop();
        //and display its value
        cout << temp_node->data << " ";
        if(temp_node->leftPtr != nullptr)
            //Put left child of node just removed from queue into queue
            temp.push(temp_node->leftPtr);
        if(temp_node->rightPtr != nullptr)
            //Put right child of node just removed from queue into queue
            temp.push(temp_node->rightPtr);
    }
    cout << endl;
}

int findHeight
    (
    TreeNode* node //in
    )
{
    if(node == nullptr)
        return -1;
    else
        return 1 + max(findHeight(node->leftPtr),findHeight(node->rightPtr));
}