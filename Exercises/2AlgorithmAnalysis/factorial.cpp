#include <chrono>
#include <windows.h> // use Windows
#include <cstdlib>
#include <functional>
#include <iostream>
using namespace std;


/**
 * Time the execution of a factorial function.
 *
 * Students using g++ on Windows should modify this function as shown in
 * https://www.engr.mun.ca/~anderson/teaching/4892/exercises/0-intarray/windows-time.
 */
void timeFactorialFunction(std::function<long (int)>, int n);

//! Time the execution of a fibonacci function.
void timeFibonacciFunction(std::function<long (int)> f, int n);

//! Calculate the factorial of a number, recursively.
uint64_t recursive(int n);

//! Calculate the factorial of a number, iteratively.
uint64_t iterative(int n);

//! Calculate the nth fibonacci number, recursively.
long fib_recur(int n);

//! Calculate the nth fibonacci number, iteratively.
long fib_iter(int n);

#include <iostream>
using namespace std;

// int main(int argc, char *argv[])
// {
//    if (argc < 2)
//    {
//        cerr << "Usage:  " << argv[0] << " <n>\n";
//        return 1;
//    }

//    char *end;
//    int n = strtol(argv[1], &end, 10);
//    if (*end != '\0')
//    {
//        cerr << "Invalid value of n: '" << argv[1] << "'\n";
//        return 1;
//    }

//    cout << "Recursive: ";
//    timeFactorialFunction(recursive, n);

//    cout << "Iterative: ";
//    timeFactorialFunction(iterative, n);

//    cout << "Fibonacci Recursive: ";
//    timeFibonacciFunction(fib_recur, n);

//    cout << "Fibonacci Iterative: ";
//    timeFibonacciFunction(fib_iter, n);

//    return 0;
// }

int main()
{
   for(int i=10; i<21; i++) {
       cout << "Factorial Recursive: ";
       timeFactorialFunction(recursive, i);

       cout << "Factorial Iterative: ";
       timeFactorialFunction(iterative, i);

//        cout << "Fibonacci Recursive: ";
//        timeFibonacciFunction(fib_recur, i);
//
//        cout << "Fibonacci Iterative: ";
//        timeFibonacciFunction(fib_iter, i);
   }

   system("pause");//to show "Press any key to continue" in the console
   return 0;
}

void timeFactorialFunction(std::function<long (int)> f, int n)
{
    uint64_t result;

/*    auto start = chrono::high_resolution_clock::now();
    result = f(n);
    auto end = chrono::high_resolution_clock::now();

    cout << "Calculated " << n << "! = " << result
         << " in " << (end - start).count() << " ns\n";*/

    // use Windows time
    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);
    result = f(n);
    QueryPerformanceCounter(&end);

    cout << "Calculated " << n << "! = " << result
         << " in " << (end.QuadPart - start.QuadPart) << " ns\n";

}

void timeFibonacciFunction(std::function<long (int)> f, int n)
{
    long result;
    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);
    result = f(n);
    QueryPerformanceCounter(&end);

    cout << "Calculated " << n << "th Fibonacci = " << result
         << " in " << (end.QuadPart - start.QuadPart) << " ns\n";
}

uint64_t recursive(int n)
{
    if(n==0){
        return 1;
    }
    return n * recursive(n-1);
}

uint64_t iterative(int n)
{
    uint64_t result = 1;
    while(n > 0){
        result *= n;
        n -= 1;
    }
    return result;
}

long fib_recur(int n)
{
    if(n<2){
        return n;
    }
    return fib_recur(n-1) + fib_recur(n-2);
}

long fib_iter(int n)
{
    long current=1;
    long last=1;
    long next=1;
    if(n<0){
        throw "n is negative!";
    }
    for(int i=2; i<n; ++i){
        next = last + current;
        last = current;
        current = next;
    }
    return next;
}