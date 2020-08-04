# Definition

Sacrifice: no ordering

The **hash table** is a data structure that provides **constant-time insertion, lookup and removal** of elements that have two properties: 

- **Equality test**:  a test of whether or not two values (or two keys) are the same

  ```c++
  bool operator == (const T &other)
  {	return /* whether or not these are the same */	}
  ```

- **Hash function**: elements can be processed with a *hash function* to produce an integer *hash code*.

  A hash table stores values in an array with index derived from elements' values, *i.e.*, hash code derived from hash function.

  ```c++
  index = hash(value)
  table[index] = value
  ```

  a good hash function is expected to provide a different code to every value.

  A simple example: mod % 

Problem: ***hash collision***: two different values hash to the same index

Solution:

 1. **chaining**: keep a list of all elements that hash to the same code

    the table’s *load factor* $\lambda=\frac{N}{M}$, $N$: number of elements in the hash table, $M$: size of the table

    - choose a table size that is a prime number
    - keep $\lambda\approx1$ 
      - Higher than that and we need to do more iteration to find the right elements; 
      - lower than that and we’re wasting space that probably isn’t required.

 2. **probing**

