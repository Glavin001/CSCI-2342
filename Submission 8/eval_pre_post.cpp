//eval_pre_post.cpp
//Iqbal:Arsum:A00351433:CSC34218
//Submission 08: Evaluating Prefix and Postfix Expressions

/*
UPDATE 1 @ 2:09 AM on 8/03/2013 : Started Program
UPDATE 2 @ 7:25 PM on 10/03/2013 : Finished Prefix
UPDATE 3 @ 11:45 PM on 10/03/2013 : 2 error checking doesn't work for 
postfix expression (Not enough operands and reached unexpectedly)
Otherwise , program works perfectly fine
*/

#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstdlib>

using namespace std;

#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::Pause;

//If you want any global constants, put them here.

void checkPostFix
    (
    vector<string> a,
    bool& successful
    );

/**<
Displays a brief program usage description on the standard output.
@param a , the vector that contains the postfix expression
@param successful, returns true if valid expression else false
@pre vector a is created
@post returns true if the postfix expression is valid
*/

void checkPreFix
    (
    deque<string> a,
    bool& successful
    );

/**<
Displays a brief program usage description on the standard output.
@param a , the deque that contains the prefix expression
@param successful, returns true if valid expression else false
@pre deque a is created
@post returns true if the prefix expression is valid
*/

void DisplayUsage();

/**<
Displays a brief program usage description on the standard output.
@pre None
@post A program usage description has been displayed, with a pause
at the end for the user to press Enter to continue.
*/

void readPostFix
    (
    vector<string> a,
    int &finalValue
    );

/**<
Tries to read a valid expression from a string stream
@param a, the vector that contains the post order expression
@param finalValue that will contain the final result of the expression
@pre a vector has been created
@post the post order expression has been succesfully evaluated
*/

void readPreFix
    (
    deque<string> a,
    int &finalValue
    );

/**<
Tries to read a valid expression from a string stream
@param a, the deque that contains the pre order expression
@param finalValue that will contain the final result of the expression
@pre a deque has been created
@post the pre order expression has been succesfully evaluated
*/

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        Scobey::DisplayOpeningScreen("Iqbal:Arsum:A00351433:CSC34218",
            "Submission 08: Evaluating Prefix and Postfix Expressions");
        DisplayUsage();
        return 1;
    }
    vector<string> first;
    deque<string> second;
    for(int i = 1; i < argc ; i++)
        first.push_back(argv[i]);
    copy(first.begin(),first.end(),front_inserter(second));
    
    string temp = first[0];
    int tempNum = atoi(temp.c_str());
    //do postfix
    if(tempNum > 0)
    {
        int postOrderVal = 0;
        bool success = true;
        checkPostFix(first,success);
        if(success == true)
        {
            readPostFix(first,postOrderVal);
            copy(first.begin(),first.end(),ostream_iterator<string>(cout," "));
            cout << "= " << postOrderVal << endl;
        }
        else if(success = false)
            return 1;
    }
    //do prefix
    else
    {
        int preOrderVal = 0;
        bool success = true;
        checkPreFix(second,success);
        if(success == true)
        {
            readPreFix(second,preOrderVal);
            copy(first.begin(),first.end(),ostream_iterator<string>(cout," "));
            cout << "= " << preOrderVal << endl;
        }
        else if(success == false)
            return 1;
    }
}


void DisplayUsage()
{
    cout <<"This program evaluates any valid prefix or postfix "
        "expression which\ncontains positive integer operands and the "
        "operators +, -, * and/or /.\nThe expression to be evaluated "
        "must be entered on the command line.\nA single positive integer "
        "also evaluates as itself."

        "\n\nTypical usage examples:"
        "\n> eval_pre_post + * 2 3 4"
        "\n+ * 2 3 4 = 10"
        "\n> eval_pre_post 2 3 4 + *"
        "\n2 3 4 + * = 14"
        
        "\n\nThe following errors are recognized and reported:"
        "\n\nFor prefix expressions:"
        "\nError: End of prefix expression reached unexpectedly."
        "\nError: Bad operator ? encountered evaluating prefix expression."
        "\nError: Extraneous characters found after valid prefix expression."
        "\n\nFor postfix expressions:"
        "\nError: End of postfix expression reached unexpectedly."
        "\nError: Bad operator ? encountered evaluating postfix expression."
        "\nError: Not enough operands for postfix operator ?."
        "\nError: Found too many operands when evaluating postfix expression."
        "\n";
    Pause();
}

void checkPostFix(vector<string> a,bool& successful)
{
    vector<string>::iterator p1 = a.begin();
    int opCount = 0;
    int digitCount = 0;
    while(p1 != a.end())
    {
        string temp = *p1;
        int tempNum = atoi(temp.c_str());
        if(tempNum > 0)
            digitCount++;
        else if((temp == "+")|(temp == "-")|(temp == "*")|(temp == "/"))
            opCount++;
        else
        {
            cerr << "Error: Bad operator " << *p1 << " encountered evaluating "
                "postfix expression." << endl;
            cerr << "Program is now terminating." << endl;
            Pause();
            successful = false;
            return;
        }
        p1++;
    }
    if(opCount >= digitCount)
    {
        cerr << "Error: End of postfix expression reached"
            " unexpectedly." << endl;
        cerr << "Program is now terminating." << endl;
        Pause();
        successful = false;
        return;
    }
    else if(digitCount >= opCount + 2)
    {
        cerr << "Error: Too many operands when evaluating "
            "postfix expression." << endl;
        cerr << "Program is now terminating." << endl;
        Pause();
        successful = false;
        return;
    }
}

void checkPreFix(deque<string> a,bool& successful)
{
    deque<string>::iterator p1 = a.begin();
    int opCount = 0;
    int digitCount = 0;
    while(p1 != a.end())
    {
        string temp = *p1;
        int tempNum = atoi(temp.c_str());
        if(tempNum > 0)
            digitCount++;
        else if((temp == "+")|(temp == "-")|(temp == "*")|(temp == "/"))
            opCount++;
        else
        {
            cerr << "Error: Bad operator " << *p1 << " encountered evaluating "
                "prefix expression." << endl;
            cerr << "Program is now terminating." << endl;
            Pause();
            successful = false;
            return;
        }
        p1++;
    }
    if(opCount >= digitCount)
    {
        cerr << "Error: End of prefix expression reached"
            " unexpectedly." << endl;
        cerr << "Program is now terminating." << endl;
        Pause();
        successful = false;
        return;
    }
    else if(digitCount >= opCount + 2)
    {
        cerr << "Error: Extraneous characters found after valid "
            << "prefix expression." << endl;
        cerr << "Program is now terminating." << endl;
        Pause();
        successful = false;
        return;
    }
}

void readPostFix(vector<string> a,int &finalValue)
{
    stack<int> value;
    int result =0;
    //while more tokens (operands or operators) to read
    vector<string>::iterator p1 = a.begin();
    while(p1 != a.end())
    {
        //if token is an operand
        string temp = *p1;
        int tempNum = atoi(temp.c_str());
        if(tempNum > 0)
            value.push(tempNum);
        //else if token is an operator ("op", say)
        else
        {
            if((*p1 == "+")|(*p1 == "-")|(*p1 == "*")|(*p1 == "/"))
            {
                //Pop stack and put value in temp2
                int temp2 = value.top();
                value.pop();
                //Pop stack and put value in temp1
                int temp1 = value.top();
                value.pop();
                if(*p1 == "+")
                    //get result of operation
                    result = temp1 + temp2;
                else if(*p1 == "-")
                    //get result of operation
                    result = temp1 - temp2;
                else if(*p1 == "*")
                    //get result of operation
                    result = temp1 * temp2;
                else if(*p1 == "/")
                    //get result of operation
                    result = temp1 / temp2;
            }
            //Push the value of temp1 op temp2 back onto stack
            value.push(result);
        }
        p1++;
    }
    //get value from stack and return it
    finalValue = value.top();
}

void readPreFix(deque<string> a,int &finalValue)
{
    stack<int> value;
    int result = 0;
    //while more tokens (operands or operators) to read
    deque<string>::iterator p1 = a.begin();
    while(p1 != a.end())
    {
        string temp = *p1;
        int tempNum = atoi(temp.c_str());
        //if token is an operand
        if(tempNum > 0)
            value.push(tempNum);
        //else if token is an operator ("op", say)
        else
        {
            if((*p1 == "+")|(*p1 == "-")|(*p1 == "*")|(*p1 == "/"))
            {
                //Pop stack and put value in temp1
                int temp1 = value.top();
                value.pop();
                //Pop stack and put value in temp2
                int temp2 = value.top();
                value.pop();
                if(*p1 == "+")
                    //get result of operation
                    result = temp1 + temp2;
                else if(*p1 == "-")
                    //get result of operation
                    result = temp1 - temp2;
                else if(*p1 == "*")
                    //get result of operation
                    result = temp1 * temp2;
                else if(*p1 == "/")
                    //get result of operation
                    result = temp1 / temp2;
            }
            //Push the value of temp2 op temp1 back onto stack
            value.push(result);
        }
        p1++;
    }
    //get value from stack and return it
    finalValue = value.top();
}