/********************Exercise for 1 Jun 2020******************/

#include <iostream>
#include <list>
#include <windows.h> // to use windows time
#include <random>
#include <ctime>
#include <fstream>

/***********Pseud-code for list*************/
/*
 *for(auto i = list.begin(); i != list.end(); i++)
 * {
 *      if (*i % 10 == 0) list.erase(i);
 *  }
 * asymptotic complexity should be O(n^2),
 * assuming the time complexity of list.erase is O(n)
 *
 *for(auto i = vector.begin(); i != vector.end(); i++)
 * {
 *      if (*i % 10 == 0) vector.erase(i);
 *  }
 *  asymptotic complexity should be O(n^2),
 *  assuming the time complexity of vector.erase is O(1)
 */
/******************************************/

template <class T>
void removeMul10(T &container)
{
    auto idx = container.begin();
    while(idx != container.end()){
        if(*idx % 10 == 0)
        {
            idx = container.erase(idx);
        }
        else {idx++;}
    }
}

//! random initialize an array of a particular size, whose range is between MIN and MAX
template <typename T>
T initContainer(int size)
{
    T contr(size);
    std::default_random_engine e(time(NULL));
    //generate random number between 0 and 10
    std::uniform_int_distribution<int> u(0, 10);
    for(auto i=contr.begin(); i!=contr.end(); i++)
    {
        //to make sure at least half of elements are multiples of 10
        *i = (u(e)%2)==0?u(e)*10:u(e);
    }
    return contr;
}

//! print container (for test)
template <typename T>
void printContainer(T contr)
{
    for (auto i = contr.begin(); i != contr.end(); i++)
        std::cout << *i << " ";
    std::cout << '\n';
}

int main()
{
    //Open file in write mode
    std::ofstream outfile;
    outfile.open("time.txt");
    //Write the header
    outfile << "Size List Vector\n";

    LARGE_INTEGER start, end;

    // iterate different size
    for(int size = 1000; size < 1e5; size += 1000)
    {
        //initialize a list for a particular size
        auto list = initContainer<std::list<int>>(size);
        //count time used for remove function
        QueryPerformanceCounter(&start);
        removeMul10(list);
        QueryPerformanceCounter(&end);

        std::cout << "Remove the list, vector of size " << size
                << " in " << (end.QuadPart - start.QuadPart) << " us" ;
        outfile << size << ' ' << (end.QuadPart - start.QuadPart) << ' ';

        //initialize a vector for a particular size
        auto vector=initContainer<std::vector<int>>(size);
        //count time used for remove function
        QueryPerformanceCounter(&start);
        removeMul10(vector);
        QueryPerformanceCounter(&end);

        std::cout << ",  " << (end.QuadPart - start.QuadPart) << " us" << '\n';
        outfile << (end.QuadPart - start.QuadPart) << '\n';
    }

    outfile.close();

    system("Pause");
    return 0;
}


