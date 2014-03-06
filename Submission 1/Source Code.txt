//process_names.cpp
//Iqbal:Arsum:A00351433:csc34218
//Submission 01: Processing Names
#include "process_names.hpp"
void helper(vector<string> fullName, int a);
int main()
{
    srand((unsigned int)time(0));
    vector<string> firstN, LastN, LastNVector;
    DisplayOpeningScreen(MY_ID_INFO,SUBMISSION_ID_INFO);
    Menu menu; menu.setTitle("Menu"); AddOptionsToMenu(menu); menu.display();
    int choice; choice = menu.getChoice();
    while(choice > 0)
    {
        if(choice == 1)
        {
            cout << "Program is now terminating.\n"; Pause(); return 0;
        } 
        if(choice == 2)
        {
            DisplayProgramInfo(); Pause();
        }
        if(choice == 3)
        {
            vector<string> first, second;firstN.clear(),LastN.clear();
            first.assign(NAMES_FEMALE,NAMES_FEMALE + 300);
            first.insert(first.end(),NAMES_MALE,NAMES_MALE+300);
            second.assign(NAMES_FAMILY,NAMES_FAMILY + 100);
            for (int i = 0; i < 24; i++)
            {
                int firstRand = rand() % 600, LastRand = rand() % 100;
                firstN.push_back(first.at(firstRand)+" "+ second.at(LastRand));
                LastN.push_back(second.at(LastRand)+", "+ first.at(firstRand));
            }
            cout << "Names have now been generated." << endl; Pause();
        }
        if(choice == 4)
            helper(firstN,1);
        if(choice == 5)
            helper(firstN,0);
        if(choice == 6)
        {
            sort(LastN.begin(),LastN.end());
            for(vector<int>::size_type i=0; i<LastN.size();i++)
            {
                int a = LastN.at(i).find(",");
                string lastName = LastN.at(i).substr(0,a);
                string firstName = LastN.at(i).substr(a+2);
                LastNVector.push_back(firstName +" "+lastName);
            }
            helper(LastNVector,1);
        }
        if(choice == 7)
            helper(LastN,0);
        menu.display(); choice = menu.getChoice();
    }
    cout << "Program now terminating." << endl;
    Pause();
}
void helper(vector<string> fullName,int a)
{
    if(a==0)
        sort(fullName.begin(),fullName.end());
    copy(fullName.begin(),fullName.end(),ostream_iterator<string>(cout,"\n"));
    Pause();
}