//encrypt_decrypt.cpp
//Iqbal:Arsum:A00351433:csc34218
//Submission 02
//Encrypting and Decrypting Textfiles

/*
UPDATE 1 @ 7:37 PM on 16/01/2013 : Started Program
UPDATE 2 @ 5:59 PM on 18/01/2013 : Finished Encoding/Decoding
UPDATE 3 @ 7:18 PM on 19/01/2013 : Finished Program
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <iterator>

using namespace std;

#include "utilities.h"

using Scobey::Menu;
using Scobey::Pause;
using Scobey::TextItems;
using Scobey::DisplayOpeningScreen;
using Scobey::ReadString;
using Scobey::DisplayTextfile;
using Scobey::userSaysYes;

const TextItems TEXT("encrypt_decrypt.txt");
vector<char> key(0);
vector<char> ascii(0);

void BuildMenu
    (
    Menu& menu
    );

/**<
@return void
@param menu is the menu that is going to be built.
@pre menu has been initialized.
@post menu was succesfully built. Titles are set as well as user options.
*/

void EncodeFiles
    (
    ifstream& inFile, // in
    ofstream& outFile // out
    );

/**<
@return void
@param inFile is the file that is going to be encoded.
@param outFile is the file in which the encoded file will be stored in.
@pre inFile and outFile are initialized and open.
@post Encoding was succesful from inFile onto outFile. outFile should now
contain numbers. Files are still open.
*/

void DecodeFiles
    (
    ifstream& inFile, // in
    ofstream& outFile // out
    );

/**<
@return void
@param inFile is the file that contains the encoded message
@param outFile is the file in which the encoded message is decoded in
@pre inFile and outFile are initialized and open.
@post Decoding was succesful from inFile onto outFile. outFile should now
contain plain text. Files are still open.
*/

void CompareFiles
    (
    string& originalFile,
    string& decodedFile
    );

/**<
@return void
@param originalFile is the original file that was supposed to be encoded
@param decodedFile is the file that was decoded using DecodedFiles().
@pre originalFile and decodedFile are initialized and open.
@post both originalFile and decodedFile were succesfully compared.
*/

void generateKey
    (
    vector<char>& key
    );

/**<
@return void
@param key that will contain the key to use when encoding/decoding
@pre key is an empty vector
@post succesfully generated the key
*/

int main()
{
    DisplayOpeningScreen("Iqbal:Arsum:A00351433:csc34218",
        "Submission 02: Encrypting and Decrypting Textfiles");
    for(int i = 32; i <=126 ; i++)
    {
        char a = i;
        ascii.push_back(a);
    }
    Menu menu;
    BuildMenu(menu);
    int choice;
    string fileName;
    string phrase;
    do
    {
        menu.display();
        choice = menu.getChoice();
        //Quit
        if(choice == 1)
        {
            cout << "Program now terminating." << endl;
            Pause();
            return 0;
        }
        //Display Program Info
        if(choice == 2)
        {
            TEXT.displayItem("Program Description");
        }
        //Encrypt
        if(choice == 3)
        {
            cout << "Please enter names of input file (plain text) and output "
            << "file (encrypted).\nInput file must exist and output file "
            << "must be writable (no error checking).\nInput file? ";
            string inputFile;
            cin >> inputFile;
            ifstream infile;
            infile.open(inputFile.c_str());
            cout << "Output file? ";
            string outputFile;
            cin >> outputFile;
            ofstream outfile;
            outfile.open(outputFile.c_str());
            cout << "\nWe need a phrase for the encryption.\nWould you like "
            << "to read that phrase from a file? (y/[n]) ";
            string choice;
            cin >> choice;
            if(choice == "yes" || choice == "y")
            {
                cout << "Enter name of file containing phrase: ";
                cin >> fileName;
                ifstream infile;
                key.clear();
                infile.open(fileName.c_str());
                string temp;
                char ch;
                while(getline(infile,temp,'\0'))
                {
                    for(unsigned int i = 0 ; i < temp.length() ; i++)
                    {
                        ch = temp[i];
                        key.push_back(ch);
                    }
                }
                generateKey(key);
            }
            else if(choice == "no"||choice == "n"||choice !="yes"||choice!="y")
            {
                cout << "OK, then enter phrase on the line below:" << endl;
                cin.ignore(1);
                key.clear();
                getline(cin, phrase);
                for (unsigned int i = 0; i < phrase.size(); i++)
                    key.push_back(phrase[i]);
                generateKey(key);
            }
            EncodeFiles(infile,outfile);
            cin.ignore(1);
            cout << "\nFile has been encrypted."<< endl;
            Pause();
        }
        //Decrypt
        if(choice == 4)
        {
            cout << "Please enter names of input file (encrypted) and output "
                << "file (plain text).\nInput file must exist and output file"
                << " must be writable (no error checking).\nInput file? ";
            string inputFile;
            cin >> inputFile;
            ifstream infile;
            infile.open(inputFile.c_str());
            cout << "Output file? ";
            string outputFile;
            cin >> outputFile;
            ofstream outfile;
            outfile.open(outputFile.c_str());
            cout << "\nWe need a phrase for the decryption.\nWould you like "
               << "to read that phrase from a file? (y/[n]) ";
            string choice;
            cin >> choice;
            if(choice == "yes" || choice == "y")
            {
                cout << "Enter name of file containing phrase: ";
                cin >> fileName;
                ifstream infile;
                key.clear();
                infile.open(fileName.c_str());
                string temp;
                char ch;
                while(getline(infile,temp,'\0'))
                {
                    for(unsigned int i = 0 ; i < temp.length() ; i++)
                    {
                        ch = temp[i];
                        key.push_back(ch);
                    }
                }
                generateKey(key);
            }
            else if(choice == "no"||choice == "n"||choice !="yes"||choice!="y")
            {
                cout << "OK, then enter phrase on the line below:" << endl;
                key.clear();
                getline(cin, phrase);
                for (unsigned int i = 0; i < phrase.size(); i++)
                    key.push_back(phrase[i]);
                generateKey(key);
            }
            DecodeFiles(infile,outfile);
            cin.ignore(1);
            cout << "\nFile has been decrypted."<< endl;
            Pause();
        }
        //Display File
        if(choice == 5)
        {
            string fileName;
            ReadString("Enter name of file to display: ", fileName);
            DisplayTextfile(fileName);

        }
        //Compare
        if(choice == 6)
        {
            cout << "Enter name of first file: ";
            string file1;
            cin >> file1;
            cout << "Enter name of second file: ";
            string file2;
            cin >> file2;
            CompareFiles(file1,file2);
        }
    }
    while(choice > 0);
}

void BuildMenu(Menu& menu)
{
    menu.setTitle("Menu");
    menu.addOption("Quit");
    menu.addOption("Get Info");
    menu.addOption("Encrypt a file");
    menu.addOption("Decrypt a file");
    menu.addOption("Display a file");
    menu.addOption("Compare two files");
}

void EncodeFiles(ifstream& inFile,ofstream& outFile)
{
    string temp;
    int count = 0;
    char ch;
    while(getline(inFile,temp,'\n'))
    {
        for(unsigned int i = 0 ; i < temp.length() ; i++)
        {
            ch = temp[i];
            int temp = (int)ch;
            outFile << key.at(temp-32);
        }
        outFile << '\n';
    }
}

void DecodeFiles(ifstream& inFile,ofstream& outFile)
{
    string temp;
    int count = 0;
    char ch;
    while(getline(inFile,temp,'\n'))
    {
        for(unsigned int i = 0 ; i < temp.length() ; i++)
        {
            ch = temp[i];
            vector<char>::iterator p;
            p = find(key.begin(),key.end(),ch);
            int position = distance(key.begin(),p);
            outFile << ascii.at(position);
        }
        outFile << '\n';
    }
}

void CompareFiles(string& originalFile,string& decodedFile)
{
    ifstream File1;
    ifstream File2;
    File1.open(originalFile.c_str());
    File2.open(decodedFile.c_str());
    string command = "fc ";
    command += originalFile;
    command += " ";
    command += decodedFile;
    system(command.c_str());
    cin.ignore(1);
    Pause();
}

void generateKey(vector<char>& key)
{
    sort(key.begin(),key.end());
    key.erase(unique(key.begin(), key.end()), key.end());
    reverse(key.begin(),key.end());
    for(int i = 32; i <=126 ; i++)
    {
        char a = i;
        vector<char>::iterator p;
        p = find(key.begin(),key.end(),a);
        if(p == key.end())
            key.push_back(a);
    }
    reverse(key.begin(),key.end());
}