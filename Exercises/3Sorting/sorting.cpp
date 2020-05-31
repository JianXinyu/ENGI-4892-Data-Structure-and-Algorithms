/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "sorting.h"

using namespace std;


template<typename T>
ostream& operator << (ostream& o, const vector<T>& v)
{
    o << "[";
    for (const auto& x : v)
    {
        o << " " << x;
    }
    o << " ]";

    return o;
}


int main()
{
    /***********************Insertion Sort Test*****************************/
    vector<int> numbers = { 1, 8, 4, 2, 9 };
    insertionSort(numbers.begin(), numbers.end(), less<int>());

    cout << "Sorted: " << numbers << "\n";

    vector<string> names = { "Alice", "Joe", "Eve", "Bob" };
    insertionSort(names.begin(), names.end(), less<string>());

    cout << "Sorted: " << names << "\n";

    vector<unique_ptr<string>> uniqueNames;
    uniqueNames.emplace_back(new string("Beorn"));
    uniqueNames.emplace_back(new string("Aiken"));

    insertionSort(uniqueNames.begin(), uniqueNames.end(),
            //
            // std::less<unique_ptr<string>>() will end up comparing pointer
            // values rather than string characters, so let's implement our
            // own comparison function:
            //
                  [](const unique_ptr<string> &a, const unique_ptr<string>& b)
                  {
                      return (*a < *b);
                  });

    cout << "Sorted:\n";
    for (const auto &s : uniqueNames)
    {
        cout << " - " << *s << "\n";
    }

    /**********************************Radix Sort Test**************************/
    vector<int> intVect = initIntVector(20);
    radixSort(intVect.begin(), intVect.end());
    cout << "Randix Sorted: " << intVect << "\n";

    //the strings must have same length
    vector<string> names1 = { "Ali", "Joe", "Eve", "Bob" };
    radixSortString(names1.begin(), names1.end(), 3);
    cout << "Randix Sorted: " << names1 << "\n";

    system("pause");//to show "Press any key to continue" in the console
    return 0;
}

