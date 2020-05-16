/*
 * Copyright 2018-2019 Jonathan Anderson
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

#include <cassert>
#include <memory>
#include <string>
#include <vector>

//! Add two values together
//double add(double x, double y);
template <typename T>
T add(T x, T y)
{
    return x + y;
}
/**
 * Calculate the average of a set of values.
 *
 * @returns the arithmetic mean of the values, or 0 if `values`.size() == 0
 */
//double average(std::vector<double> values);
//template <typename T>
//T average(std::vector<T> values);
template <typename T>
T average(std::vector<T> values)
{
    if (values.empty())
    {
        return 0;
    }

    T sum = 0;
    for (T v : values)
    {
        sum = add(sum, v);
    }

    return sum / values.size();
}

/**
 * A data structure that holds a growable array, with the optimization that
 * small arrays are stored directly in the object rather than allocated from
 * the heap.
 */
template <class T, int s>
class GrowableArray
{
public:
    GrowableArray()
            : capacity_(s), size_(0)
    {
    }

    //! Add a value to the back of the array
    GrowableArray& operator << (T value)
    {
        if (size_ >= capacity_)
        {
            size_t newCapacity = 2 * capacity_;
            std::unique_ptr<T> bigger(new T[newCapacity]);

            // To be really clever, change this to std::copy():
            for (size_t i = 0; i < size_; i++)
            {
                bigger.get()[i] = (*this)[i];
            }

            largeArray_.swap(bigger);
            capacity_ = newCapacity;
        }

        size_ += 1;
        (*this)[size_ - 1] = value;

        return *this;
    }

    //! Access an element within the array
    T& operator[] (size_t index)
    {
        assert(size_ <= capacity_);

        if (index >= size_)
        {
            // TODO: real error handling?
            throw std::string("eek!");
        }

        if (largeArray_)
        {
            return largeArray_.get()[index];
        }
        else
        {
            return smallArray_[index];
        }
    }

    //! Average
    T average()
    {
        if (size_ == 0)
        {
            return 0;
        }

        T sum = 0;
        T value;
        for (int i = 0; i < size_; i++)
        {
            if (largeArray_)
            {
                value = largeArray_.get()[i];
            }
            else
            {
                value = smallArray_[i];
            }
            sum = add(sum, value);
        }

        return sum / size_;
    }

private:
    /**
     * If we only need to hold a small array, it can be more efficient to
     * store it within the object itself.
     *
     * Note: this is also the optimization used by `std::string`!
     */
    T smallArray_[8];

    /**
     * A pointer to a larger array, if we need it.
     */
    std::unique_ptr<T> largeArray_;

    //! How many elements the currently-in-use array can hold.
    size_t capacity_;

    //! How many elements are actually in the array.
    size_t size_;
};