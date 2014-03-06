//find_concordance.cpp
//Iqbal:Arsum:A00351433:csc34218
//Submission 04
//Finding Concordances

/*
UPDATE 1 @ 7:37 PM on 30/01/2013 : Started Program
UPDATE 2 @ 5:22 PM on 01/02/2013 : Finished Program
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <iomanip>
#include <iterator>
#include <algorithm>

using namespace std;

#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::Pause;
using Scobey::TextItems;

const TextItems TEXT("concordance.txt");

void DisplayConcordance
    (
    map<string, set<int>> myMap //in
    );

/**<
@return void
@param myMap is the map that contains the concordance
@pre myMap already contains the concordances
@post the concordance is displayed on the standard output
*/

void GenerateConcordance
    (
    ifstream& infile, //in
    map<string, set<int>>& myMap //in
    );

/**<
@return void
@param infile is the file that contains words needed
@param myMap is the map that will contain the concordance
@post the concordance is succesfully generated
*/

void DisplayFileConcordance
    (
    ofstream& outfile, //out
    map<string, set<int>>& myMap //in
    );

/**<
@return void
@param outfile is the file that will have the concordance written to
@param myMap is the map that contains the concordance
@pre outfile is initialized and open and myMap contains the concordance
@post the concordance was succesfully displayed in outfile
*/

int main(int argc,char* argv[])
{
    map<string, set<int>> wordList;
    if(argc == 1)
    {
        DisplayOpeningScreen("Iqbal:Arsum:A00351433:csc34218",
            "Submission 05: Building Concordances");
        TEXT.displayItem("ProgramDescription");
    }
    if(argc == 2)
    {
        ifstream infile(argv[1]);
        if(!infile)
        {
            cout << "Cannot open input file " << argv[1]
            << "\nProgram now terminating."<< endl;
            Pause();
            return 0;
        }
        GenerateConcordance(infile,wordList);
        DisplayConcordance(wordList);
    }
    if(argc == 3 || argc == 4)
    {
        ifstream infile(argv[1]);
        ofstream outfile(argv[2]);
        GenerateConcordance(infile,wordList);
        DisplayFileConcordance(outfile,wordList);
        outfile.clear(); outfile.close();
        if(argc == 4)
        {
            ifstream File1(argv[2]);
            ifstream File2(argv[3]);
            string command = "fc ";
            command += argv[2];
            command += " ";
            command += argv[3];
            command += ">";
            command += "differences.txt";
            system(command.c_str());
        }
    }
}
void GenerateConcordance(ifstream& infile, map<string, set<int>>& myMap)
{
    string word;
    int count = 1;
    while(!infile.eof())
    {
        if(infile.peek() == '\n')
                count ++;
        infile >> word;
        word.erase(remove_if(word.begin(),word.end(),&ispunct),word.end());
        word.erase(remove_if(word.begin(),word.end(),&isdigit),word.end());
        if(!word.empty())
        {
            for(unsigned int i = 0; i < word.size(); i++)
                word[i] = tolower(word[i]);           
            map<string,set<int>>::iterator mapIter = myMap.find(word);
            if(mapIter != myMap.end())            
                mapIter->second.insert(count);       
            else            
                myMap[word].insert(count);
        }
    }
}
void DisplayConcordance(map<string, set<int>> myMap)
{
    int numPerLine = 0;
    map<string, set<int>>::iterator mapIter = myMap.begin();
    while(mapIter != myMap.end())
    {
        set<int>::iterator p = mapIter->second.begin();
        cout.width(15);
        cout << right <<mapIter ->first;
        while(p != mapIter->second.end())
        {
            if(numPerLine == 15)
            {
                cout << "\n";
                cout.width(16);
                numPerLine = 0;
            }
            cout << " " << *p++;
            numPerLine++;
        }
        cout << "\n";
        mapIter++;
        numPerLine = 0;
    }
}
void DisplayFileConcordance(ofstream& outfile,map<string, set<int>>& myMap)
{
    int numPerLine = 0;
    map<string, set<int>>::iterator mapIter = myMap.begin();
    while(mapIter != myMap.end())
    {
        set<int>::iterator p = mapIter->second.begin();
        outfile.width(15);
        outfile << right <<mapIter ->first;
        while(p != mapIter->second.end())
        {
            if(numPerLine == 15)
            {
                outfile << "\n";
                outfile.width(16);
                numPerLine = 0;
            }
            outfile << " " << *p++;
            numPerLine++;
        }
        outfile << "\n";
        mapIter++;
        numPerLine = 0;
    }
}