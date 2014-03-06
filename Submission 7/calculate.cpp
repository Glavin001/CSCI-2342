//calculate.cpp
//Iqbal:Arsum:A00351433:csc34218
//Submission 07
//Implementing a Simple Four-Function Calculator

/*
UPDATE 1 @ 7:35 PM on 26/02/2013 : Started Program
UPDATE 2 @ 6:55 PM on 3/03/2013 : Garbage Function Left
UPDATE 3 @ 7:43 PM on 3/03/2013 : Finished Program
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::Pause;

#include "calculator.hpp"

void DisplayUsage();
/**<
Displays a brief description of how to use the program.
@pre  None
@post Program usage description has been displayed on standard output.
*/

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        DisplayOpeningScreen("Iqbal:Arsum:A00351433:CSC34218",
        "Submission 07: Implementing a Simple Four-Function Calculator");
        DisplayUsage();
        return 1;
    }
    else
    {
        string expression;
        for(int i = 1; i < argc ; i++)
            expression += argv[i];
        istringstream newStream(expression);
        TreeNode exp;
        bool success;
        GetExpression(newStream,exp,success);
        if(success == true)
        {
            CheckForGarbage(newStream,success);
            if(success == true)
            {
                cout << endl;
                DisplayExpression(exp);
                cout << " = "<< expressionValue(exp) << endl;
            }
        }
        else if(success == false)
        {
            cout << "\nBad input! Could not compute value." << endl;
            return 0;
        }
    }
}

void DisplayUsage()
{
    cout << "\nThis program is a simple four-function calculator "
        "with command-line input.\n\nOnly integer arithmetic using "
        "four operators (+, -, *, or /) is permitted.\n\nEach line "
        "of input is limited to either a single positive integer, "
        "or a\nfully-parenthesized arithmetic expression containing "
        "only binary operators\nand positive integer operands.\n\n"
        "Extra spaces in the input are ignored, but any characters "
        "other than blank\nspaces that appear after a valid expression "
        "and on the same line will cause\nthat entire input line to be "
        "rejected as bad input.\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\nPress Enter to continue ... ";  cin.ignore(80, '\n');
}