//power_set_funs.hpp
//Iqbal:Arsum:A00351433:csc34218
//Submission 05: Building and Displaying Power Sets

/*
UPDATE 1 @ 3:47 PM on 2/09/2013 : Started Program
UPDATE 2 @ 10:10 PM on 2/10/2013 : Finished Program
*/
template<typename T>
set<set<T>> powerSet(const set<T>& sOriginal)
{
    set<T> duplicateSet = sOriginal;
    set<set<T>> bigSet;
    //if the set is empty , return the empty set
    if(duplicateSet.empty())
    {
        bigSet.insert(duplicateSet);
        return bigSet;
    }
    else
    {
        set<T>::iterator p = duplicateSet.begin();
        //create a temp variable so we can erase the original
        T temp = *p;
        duplicateSet.erase(p);
        //after removing the first value,use recursion with set that is 1 less
        set<set<T>> powerSetResult = powerSet(duplicateSet);
        set<set<T>>::iterator powerSetResultIter = powerSetResult.begin();
        while(powerSetResultIter!=powerSetResult.end())
        {
            set<T> tempSet = *powerSetResultIter;
            //add the removed element back into the set
            tempSet.insert(temp);
            //add the current set item of the reduced set
            bigSet.insert(*powerSetResultIter);
            //insert that set back into the power set
            bigSet.insert(tempSet);
            *powerSetResultIter++;
        }
        return bigSet;
    }
}
template<typename T>void
WritePowerSet(const set<set<T>>& pSet)
{
    set<set<T>>::iterator powerSetIter = pSet.begin();
    int count = 0;
    while(powerSetIter != pSet.end())
    {
        //point to the first set inside the bigSet
        set<T>::iterator insideIter = (*powerSetIter).begin();
        cout << "{";
        while(insideIter != (*powerSetIter).end())
        {
            //print the first element of the first set
            cout << *insideIter;
            insideIter++;
            //if its not the end of the first set, print the comma
            if(insideIter != (*powerSetIter).end())
                cout << ", ";
        }
        cout << "} ";
        count++;
        //if more than 4 on line , create new line
        if(count % 4 == 0)
            cout << "\n";
        powerSetIter++;
    }
}