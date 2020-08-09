#include <iostream>
#include "HashTable.h"
#include <unordered_set>
#include <windows.h> // use Windows
#include <fstream> // store the data into a file
using namespace std;

//! timer: inserts 10,000 integers (0 through 9,999) to an unsorted_set
size_t timeFunc(float loadFactor)
{
    unordered_set<int> set;
    // set the maximum load factor
    set.max_load_factor(loadFactor);

    LARGE_INTEGER start, end;
    size_t time;
    QueryPerformanceCounter(&start); // timer starts

    // inserts 10,000 integers (0 through 9,999)
    for(int i = 0; i < 10000; i++)
    {
        set.insert(i);
    }

    QueryPerformanceCounter(&end);   // time ends
    time = (end.QuadPart - start.QuadPart);
    cout << "Load Factor " << loadFactor
         <<  " Time: " << time << " ns\n";

    return time;
}


int main(int argc, char *argv[])
{
    //! Exercises for 3 Aug 2020
    HashTable t;

    for (int i = 1; i < argc; i++)
    {
        t.insert(argv[i]);
    }
    t.insert("hello");
    t.insert("world");

    for (auto b : t.bucketCounts())
    {
        cout << b.first << " " << b.second <<endl;
    }

    //! Exercises for 5 Aug 2020 Q1
    float loadFactor = 0;
    unordered_set<int> set;
    cout << "Enter the Load Factor: ";
    cin >> loadFactor;
    // set the maximum load factor
    set.max_load_factor(loadFactor);

    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start); // timer starts

    // inserts 10,000 integers (0 through 9,999)
    for(int i = 0; i < 10000; i++)
    {
        set.insert(i);
    }
    QueryPerformanceCounter(&end);   // time ends
    cout << "Calculation Time: " << (end.QuadPart - start.QuadPart) << " ns\n";


    //! Exercises for 5 Aug 2020 Q2
    //Open file in write mode
    std::ofstream outfile;
    outfile.open("time.txt");
    //Write the header
    outfile << "LoadFactor Time LoadFactor Time\n";

    float lfactor_s = 0.001; // load factor smaller than 1
    float lfactor_b = 1; // load factor biger than 1
    for(int i = 0; i < 100; i++)
    {
        outfile << lfactor_s << ' ' << timeFunc(lfactor_s) << ' ';
        outfile << lfactor_b << ' ' << timeFunc(lfactor_b) << '\n';
        lfactor_s += 0.001;
        lfactor_b += 5;
    }

    outfile.close();

    system("pause");//to show "Press any key to continue" in the console
    return 0;
}

