//anagrams.cpp
//Iqbal:Arsum:A00351433:csc34218
//Submission 03
//Finding Anagrams of words
/*
UPDATE 1 @ 5:32 PM on 25/01/2013 : Finished Program
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
#include "utilities.h"
using Scobey::DisplayOpeningScreen;
using Scobey::Pause;
int main()
{
    DisplayOpeningScreen("Iqbal:Arsum:A00351433:csc34218",
        "Submission 03: Finding Anagrams");
    cout << "This program finds all the words in a dictionary that can be "
        "formed with the\nletters of a given word (or string), and displays "
        "them in alphabetical order.\n\nEnter the name of the file containing "
        "the dictionary: ";
    string filename, chosenWord, word; bool status = false;
    cin >> filename; cin.ignore();
    ifstream infile(filename.c_str());
    if(!infile)
    {
        cout << "\nCould not open file named "<< filename;
        Pause(0,"\nProgram is now terminating."); return 0;
    }
    vector<string> myVec; vector<char> temp, temp1;
    while(getline(infile,word,'\n'))
        myVec.push_back(word);
    cout << "\nReading the dictionary ...\nThe dictionary contains "
        << myVec.size() <<" words\n"; Pause();
    cout << "Now enter a word (or any string of letters) and I'll give you\n"
        "a list of all of its anagrams (if any) found in the dictionary: ";
    getline(cin,chosenWord);
    do
    {
        for(vector<int>::size_type i=0; i<myVec.size();i++)
        {
            if(myVec.at(i).length() == chosenWord.length())
            {
                temp.clear(); temp1.clear();
                for(unsigned int j = 0 ; j < myVec.at(i).length() ; j++)
                    temp.push_back(myVec.at(i).at(j));
                for (unsigned int k = 0; k < chosenWord.length(); k++)
                   temp1.push_back(chosenWord[k]);
                sort(temp.begin(),temp.end());sort(temp1.begin(),temp1.end());
                if(temp == temp1){
                    cout << myVec.at(i)<< "\n"; status = true;}
            }
        }
        if(status == false)
            cout << "Sorry, no acronyms found for that input.\n";
        cout << "\nEnter another one (or the end-of-file character to stop): ";
        status = false;
        getline(cin,chosenWord);
    }
    while(!cin.eof());
    cin.clear();
    Pause(0,"Program is now terminating."); return 0;
}