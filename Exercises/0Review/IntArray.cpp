/*
* 1. a) What values did you choose? Why these values?
*       I choose: 1e3, 1e4, 2e4, 3e4, 4e4, 5e4, 6e4.
*       Because after several trail and error, I found that they're large enough to see the
 *      difference and prevent some noise.
 *   b) Please see "report.pdf"
*    c) Does this conform to your expectations? Explain
*       I guess the relationship between size and time is linear. The result conforms to my expectation.
*       From the code, we can see that to search for the largest number, every entry of the array is checked.
 *      Thus, when the size of array is big, time is approximately proportional to the size, i.e.,
 *      the time complexity is O(n).
 */
#include <chrono>
#include <windows.h>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <vector>
using namespace std;


class IntegerArray
{
public:
    IntegerArray()
    {
    }

    IntegerArray(std::initializer_list<int> init) : values_(init)
    {
    }

    IntegerArray(std::vector<int>&& v): values_(std::move(v))
    {
    }

    std::vector<int>::const_iterator begin() const
    {
        return values_.begin();
    }

    std::vector<int>::const_iterator end() const
    {
        return values_.end();
    }

    IntegerArray& operator << (int n)
    {
        values_.push_back(n);
        return *this;
    }

    size_t size() const
    {
        return values_.size();
    }

    /**
     * Insert value 'v' at position 'pos' within the array
     */
    std::vector<int>::iterator insert(int v, size_t pos){
        return values_.insert(begin() + pos, v);
    }
private:
    std::vector<int> values_;
};


//////////////////////////////////////////////////////////////////////////////
//Re-implement IntArray using manual memory management
// (using new to allocate and either delete or smart pointers to clean up)
// and int pointers instead of std::vector<int>::[const_]iterator.
class NewArray
{
public:
    NewArray(int size=0);
    ~NewArray();
    int *begin();
    int *end();
    NewArray& operator << (int val);
    int size() const;
private:
    int *ptr; //points to start of array
    int size_;
};

//constructor
NewArray::NewArray(int size):size_(size) {
    if(size==0){ptr = nullptr;}
    else{ptr = new int[size];}
}

//destructor
NewArray::~NewArray() {
    delete [] ptr;
}

int NewArray::size() const{
    return size_;
}
int *NewArray::begin(){
    return &ptr[0];
}

int *NewArray::end(){
    return &ptr[size_-1];
}

NewArray& NewArray::operator<<(int val){
    if(ptr){ //if array isn't empty
        int *ptr_new = new int[size_+1]; //allocate new space
        memcpy(ptr_new, ptr, sizeof(int)*size_); //copy original array
        delete [] ptr;
        ptr = ptr_new;
    }
    else{
        ptr = new int[1];
    }
    ptr[size_++] = val; //add new value
    return *this;
}
//////////////////////////////////////////////////////////////////////////////////////

// How many elements shall we store in our array?
constexpr size_t WorkingSize = 5e4;


int main(int, char*[])
{
    // Create an empty IntegerArray
    IntegerArray array;

    // Initialize random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Add random elements to the array
    for (size_t i = 0; i < WorkingSize; i++)
    {
        unsigned long r = static_cast<unsigned long>(rand());
        array << (r % WorkingSize);
    }

    //
    // Find an arbitrary number:
    //
    bool foundIt = false;
    int index = 0;

    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);
    for (int value : array)
    {
        if (value == 42)
        {
            foundIt = true;
            break;
        }

        index++;
    }
    QueryPerformanceCounter(&end);

    if (foundIt)
    {
        cout << "found the value 42 at index " << index;
    }
    else
    {
        cout << "42 is not in the IntegerArray array";
    }

    cout << " (took " << (end.QuadPart - start.QuadPart) << "  µs)\n";

    //
    // Find the largest number:
    //
    QueryPerformanceCounter(&start);
    int largest = 0;
    for (auto i = array.begin(); i != array.end(); i++)
    {
        if (*i > largest)
        {
            largest = *i;
        }
    }
    QueryPerformanceCounter(&end);

    cout << "the largest value is: " << largest
         << " (took " << (end.QuadPart - start.QuadPart) << "  µs)\n";

    QueryPerformanceCounter(&start);
//    array.insert(1, WorkingSize);
    array.insert(1, 0);
    QueryPerformanceCounter(&end);

//    cout << *(array.end()-1) << endl;
    cout << " (Inserting took " << (end.QuadPart - start.QuadPart) << "  µs)\n";

///////////////////////////////////////////////////////////////////////
    NewArray na;
    na << 1;
    na << 2;
    cout <<"New array begin:"<< *na.begin()<<endl;
    cout <<"New array end:"<< *na.end()<<endl;
    return 0;

}


std::ostream& operator << (std::ostream& o, const IntegerArray& a)
{
    o << "[";
    for (int i : a)
    {
        o << " " << i;
    }
    o << " ]\n";

    return o;
}
