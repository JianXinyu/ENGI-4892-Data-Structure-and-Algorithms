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

#ifndef SORTING_SORTING_H
#define SORTING_SORTING_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <cmath>

template<typename T>
static void swap(T &x, T &y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template<typename Comparator, typename Iter>
void bubbleSort(Iter begin, Iter end, Comparator compare = Comparator())
{
    for (auto i = begin; i != end; i++)
    {
        for (auto j = begin; j != end; )
        {
            auto current = j;
            auto next = ++j;

            if (next == end)
            {
                break;
            }

            if (compare(*next, *current))
            {
                swap(*next, *current);
            }
        }
    }
}


template<typename Iter, typename Comparator>
void insertionSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
    for(auto i = begin + 1; i != end; i++)
    {
        //begin with the last element
        auto j = i-1;
        // record the value needed to insert
        auto key = std::move(*i);
        /* Move the top (i-1)th elements, that are greater/less
         * than key, to one position ahead
         * of their current position */
        while(j >= begin && compareFn(key, *j))
        {
            *(j+1) = std::move(*j);
            // move to the previous element
            --j;
        }
        // insert the key to correct position
        *(j+1) = std::move(key);
    }
}

//! calculate how many digits in an vector
template <typename Iter>
int getExp(const Iter& begin, const Iter& end)
{
    //find the maximal integer
    auto max = std::move(*begin);
    for(auto i = begin; i != end; i++)
    {
        if (max < *i) max = std::move(*i);
    }
    //calculate its digits
    int exp = log10(max) + 1;
    return exp;
}

template <typename Iter>
void radixSort(const Iter& begin, const Iter& end)
{
    int exp = getExp(begin, end);
    //iterate every digit
    for(int i = 0; i < exp; i++)
    {
        //more than one integer could fall into same bucket, so define a 2D vector
        std::vector<std::vector<int>> buckets(10);
        for(auto j=begin; j!=end; j++)
        {
            //calculate the value on the desired significant digit
            int digitVal = *j / (int) pow(10, i) % 10;
            buckets[digitVal].push_back(std::move(*j));
        }
        auto idx = begin;
        //sort items according to their position in buckets
        //e.g. 1st item in the bucket[0] will be ranked first
        //thus items are sorted on the desired significant digit
        for(auto &thisBucket : buckets)
        {
            for(auto &val : thisBucket)
            {
                *idx = val;
                idx++;
            }
            thisBucket.clear();
        }
    }
}

//! implementation of radix sort for strings
template <typename Iter>
void radixSortString(const Iter& begin, const Iter& end, int stringLen)
{
    const int BUCKETS = 256;
    std::vector<std::vector<std::string>> buckets(BUCKETS);
    for(int pos = stringLen -1; pos >= 0; --pos)
    {
        for(auto i=begin; i!=end; i++)
        {
            auto tmp = std::move(*i);
            buckets[tmp[pos]].push_back(tmp);
        }

        auto idx = begin;
        for(auto &thisBucket : buckets)
        {
            for(auto &str : thisBucket)
            {
                *idx = std::move(str);
                idx++;
            }
            thisBucket.clear();
        }
    }
}
//! randomly initialize an integer vector of a particular size, whose range is between MIN and MAX
#define MIN 1.0
#define MAX 1000.0
std::vector<int> initIntVector(int size)
{
    std::vector<int> intVect;

    srand(time(NULL));
    intVect.reserve(size);
    for(int i=0; i<size; i++)
    {
        intVect.push_back(MIN + (int)MAX * rand() / (RAND_MAX + 1));
    }
    return intVect;
}

#endif //SORTING_SORTING_H
