//club_members.cpp
//Iqbal:Arsum:A00351433:csc34218
//Submission 06: Using a Binary File to Process Club Member Data

/*
UPDATE 1 @ 9:35 PM on 2/16/2013 : Started Program
UPDATE 2 @ 10:47 PM on 2/24/2013 : Option 7 left
UPDATE 3 @ 11:18 PM on 2/24/2013 : Finished Program
*/

using namespace std;

#include <fstream>
#include <string>
#include <cstring>

#include "utilities.h"

using Scobey::Menu;
using Scobey::Pause;
using Scobey::ReadString;
using Scobey::ReadInt;
using Scobey::ReadDouble;
using Scobey::DisplayTextfile;
using Scobey::ReadThisLine;

#include "club_members.h"

extern const string MY_ID_INFO = "Iqbal:Arsum:A00351433:csc34218";
ClubMember member;

void BuildMenu
(
    Menu& menu
)
{
    menu.setTitle("Menu");
    menu.addOption("Quit");
    menu.addOption("Get information");
    menu.addOption("Read a textfile of club member data into a "
        "working binary file");
    menu.addOption("Display all club member data from the binary file");
    menu.addOption("Display data for one or more club members from the "
        "binary file");
    menu.addOption("Add a new club member to the working binary file");
    menu.addOption("Update a club member's data in the binary file");
    menu.addOption("Write the working binary file of club member data "
        "to a textfile");
    menu.addOption("Display any textfile");
}

//option 3
void TransferTextToBinary
    (
    fstream& ioFile,
    bool& successful
    )
{
    string fileName;
    ReadString("Enter name of input textfile containing club "
        "members: ",fileName);
    ifstream inputTextFile(fileName);
    ioFile.open("working.bin",ios::binary| ios::out| ios::in| ios::trunc);
    if(!inputTextFile)
    {
        cout << "\nError opening input textfile.\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else if(!ioFile)
    {
        cout << "\nError opening working binary file."
            "\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else
    {
        string temp;
        int count = 1;
        //get the name
        while(getline(inputTextFile,temp,'\n'))
        {   
            if(count == 1)
            {
                //clear the char array
                memset(member.name,'\0',31);
                for(unsigned int i = 0 ; i < temp.length(); i++)
                    member.name[i] = temp[i];
                count++;
            }
            //get the age and balance
            getline(inputTextFile,temp,'\n');
            if(count == 2)
            {
                string::size_type space = temp.find(' ');
                string tempAge = temp.substr(0,space);
                //find the age and store it in struc
                member.age = atoi(tempAge.c_str());
                string::size_type dollar = temp.find('$');
                string tempBalance = temp.substr(dollar+1);
                //find the balance and store it in struc
                member.balance = atof(tempBalance.c_str());
                count--;
            }
            //write the struc into the binary file
            ioFile.write((char *)&member, sizeof(ClubMember));
        }
        successful = true;
        inputTextFile.close();
    }
}

//option 4
void DisplayAllMembers
    (
    fstream& ioFile,
    bool& successful
    )
{
    ioFile.clear();
    int lineNum = 0;
    if(!ioFile.is_open())
    {
        cout << "\nBinary file not yet open.\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else
    {
        //start at the beginning of file
        ioFile.seekg(0);
        while(!ioFile.eof())
        {
            //read the strucs
            ioFile.read((char *)&member, sizeof(ClubMember));
            if(!ioFile.eof())
            {
                //print the club members
                cout << "====================\n" << member.name << endl;
                cout << "Age: " << member.age << "  " << "Balance: $"
                    << member.balance << endl;
            }
            lineNum++;
            //if more than 8 members, pause
            if(lineNum == 8)
            {
                Pause();
                lineNum = 0;
            }
        }
        successful = true;
    }
}

//option 5
void DisplayOneOrMoreMembers
    (
    fstream& ioFile,
    bool& successful
    )
{
    ioFile.clear();
    if(!ioFile.is_open())
    {
        cout << "\nBinary file not yet open.\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else
    {
        string searchedName;
        ReadThisLine("Enter full or partial name of member(s) whose data "
            "you wish to display:",searchedName);
        //start at the beginning of file
        ioFile.seekg(0);
        while(!ioFile.eof())
        {
            ioFile.read((char *)&member, sizeof(ClubMember));
            if(!ioFile.eof())
            {
                //if found the searchedName(full or partial)
                if(((string)member.name).find(searchedName) != string::npos)
                {
                    //print it
                    cout << "====================\n" << member.name << endl;
                    cout << "Age: " << member.age << "  " << "Balance: $"
                        << member.balance << endl;
                }
            }
        }
        successful = true;
    }
}

//option 6
void AddNewMember
    (
    fstream& ioFile,
    bool& successful
    )
{
    if(!ioFile.is_open())
    {
        cout << "\nBinary file not yet open.\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else
    {
        ioFile.clear();
        string newMemberName;
        int newMemberAge;
        double newMemberBalance;
        //ask for info for the new club member
        ReadThisLine("Enter name of new member: ",newMemberName);
        ReadInt("Enter age of new member: ", newMemberAge);
        ReadDouble("Enter opening balance of new member: ",newMemberBalance);
        //clear the array
        memset(member.name,'\0',31);
        for(unsigned int i = 0 ; i < newMemberName.length(); i++)
            member.name[i] = newMemberName[i];
        //store the info into the struc
        member.age = newMemberAge;
        member.balance = newMemberBalance;
        ioFile.seekg(0, ios::end);
        //write the struc into the binary file
        ioFile.write((char *)&member, sizeof(ClubMember));
        ioFile.seekg(0);
        successful = true;
    }
}

//option 7
void UpdateMemberData
    (
    fstream& ioFile,
    bool& successful
    )
{
    //store the position of the stream(later to be used for seekg/p)
    streamoff position;
    ioFile.clear();
    int count = 0;
    if(!ioFile.is_open())
    {
        cout << "\nBinary file not yet open.\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else
    {
        string identity;
        ReadThisLine("Enter enough of the member's name to "
            "identify him/her: ", identity);
        //start at beginning
        ioFile.seekg(0);
        while(!ioFile.eof())
        {
            //make a temporary position to hold the beginning of the struc
            streamoff tempPos = ioFile.tellg();
            //read the binary file
            ioFile.read((char *)&member, sizeof(ClubMember));
            if(!ioFile.eof())
            {
                if(((string)member.name).find(identity) != string::npos)
                {
                    //put the beginning of the struc into the position
                    position = tempPos;
                    //print club member
                    cout << "====================\n" << member.name << endl;
                    cout << "Age: " << member.age << "  " << "Balance: $"
                        << member.balance << endl;
                    count++;
                }
            }
        }
        if(count != 1)
        {
            cout << "\n=====>Either more than one member, or no members, "
                "matched your input.\n=====>You need to identify a "
                "unique club member to update.\n=====>Try again with "
                "more specific input.\n" << endl;
            Pause();
            successful = false;
        }
        if(count == 1)
        {
            cout << "\nUpdating data for the above club member." << endl;
            string choice;
            do
            {
                cout << "Enter n/a/b to update name/age/balance, or "
                    "q to quit updating this member: ";
                getline(cin,choice);
                if(choice == "q")
                {
                    cout << "\nOK, no more updates for this club member "
                        "at this time." << endl;
                    Pause();
                    successful = true;
                }
                if(choice == "n")
                {
                    string revisedName;
                    ReadThisLine("Enter revised name: ", revisedName);
                    //clear the array
                    memset(member.name,'\0',31);
                    for(unsigned int i = 0 ; i < revisedName.length(); i++)
                        //store the new name into the struc
                        member.name[i] = revisedName[i];
                }
                if(choice == "a")
                {
                    int newAge;
                    ReadInt("Enter revised age: ", newAge);
                    //store new age in struc
                    member.age = newAge;
                }
                if(choice == "b")
                {
                    double newBalance;
                    ReadDouble("Enter revised balance: ", newBalance);
                    //store new balance in struc
                    member.balance = newBalance;
                }
            }
            while(choice != "q");
        }
        ioFile.clear();
        //go to the position 
        ioFile.seekg(position);
        ioFile.seekp(position);
        //finally write the info back into the binary file
        ioFile.write((char *)&member, sizeof(ClubMember));
        successful = true;
    }
}

//option 8
void WriteTextArchiveAndDeleteBinary
    (
    fstream& ioFile,
    bool& successful
    )
{
    ioFile.clear();
    string outputFile;
    ReadThisLine("Enter name of output textfile for archiving "
        "club member data: ",outputFile);
    ofstream outFile(outputFile);
    if(!outFile)
    {
        cout << "\nError opening out textfile.\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else if(!ioFile.is_open())
    {
        cout << "\nBinary file not yet open.\nReturning to menu." << endl;
        Pause();
        successful = false;
    }
    else
    {
        //start at beginning of file
        ioFile.seekg(0);
        while(!ioFile.eof())
        {
            //read the binary file
            ioFile.read((char *)&member, sizeof(ClubMember));
            if(!ioFile.eof())
            {
                //store the info from binary file back into a txt file
                outFile << member.name << endl;
                outFile << member.age << " $" << member.balance << endl;
            }
        }
        successful = true;
        //clear the txtfile as well as the binary file
        outFile.clear(); outFile.close();
        ioFile.clear(); ioFile.close();
        //delete the binary file
        remove("working.bin");
    }
}

//option 9
void DisplayAnyTextfile()
{
    string fileName;
    ReadString("Enter name of file to display: ", fileName);
    DisplayTextfile(fileName);
}