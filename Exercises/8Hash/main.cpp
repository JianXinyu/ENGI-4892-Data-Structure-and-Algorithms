#include <iostream>
#include "HashTable.h"

using namespace std;
int main(int argc, char *argv[])
{
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
    return 0;
}
