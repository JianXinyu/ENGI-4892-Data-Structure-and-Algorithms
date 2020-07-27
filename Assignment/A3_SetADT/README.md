Implement a simple set ADT.

A *set* is a data structure that holds values, ignoring duplicates. In this assignment, you will implement a simple ADT (abstract data type) for a set. You do not need to implement set operations such as computing unions and intersections; instead, you only need to implement the methods declared in [Set.h](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/assignment/3/Set.h):

```C++
/*
 * Copyright 2020 Jonathan Anderson
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

#ifndef SET_H_
#define SET_H_

#include <set>


/**
 * A set that holds values, ignoring duplicates.
 */
template<typename T>
class Set
{
public:
	//! Add an element to this set.
	void insert(T);

	//! Is a specified element already in the set?
	bool contains(const T&) const;

	//! How many values are in this set?
	size_t size() const;

	// Iterators over const and non-const sets:
	Iterator begin();
	ConstIterator begin() const;

	Iterator end();
	ConstIterator end() const;

	/**
	 * Look up a specific value within this set.
	 *
	 * This should return an iterator that is equal to end() if the value
	 * is not found.
	 */
	Iterator find(const T&);
	ConstIterator find(const T&) const;
};

#endif
```

I will test your code with test cases such as the following:

```C++
Set<int> s;
for (int n : { 22, 93 })
{
	s.insert(n);
}

CheckInt(22, *s.find(22));
Check(s.find(99) == s.end(), "find(99) should equal end()");
```

For this assignment, you may not use **any** of the STL: you must implement **everything** yourself. Also as always, please ensure that your assignment submission is **your own individual work**. Finally, if you’re not clear about anything, please ask!