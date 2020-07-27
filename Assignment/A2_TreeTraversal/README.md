Implement an iterator that traverses over a binary tree.

Starting with the binary search tree code in the file [BST.h](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/assignment/2/BST.h), complete the following methods for tree traversal:

```C++
/**
 * Returns an iterator that can be used to traverse the tree in the given order.
 *
 * This iterator should visit every node in the tree exactly once, after which
 * it should test equal to the iterator returned from `end()`.
 */
Iterator begin(enum class Traversal);

/**
 * The end of a tree traversal.
 *
 * The iterator returned by this method should be usable as the end-of-iteration
 * marker for any iterator on this tree, whether it was traversing the tree in
 * pre-, in- or post-order.
 */
Iterator end();
```

I will test your code with test cases such as the following:

```C++
// Create a tree of integers:
BinarySearchTree<int> t;

// Fancy way of not having to write BinarySearchTree<int> twice:
const auto Order = decltype(t)::Traversal::InOrder;

// Insert the values 4, 2, 6, 1, 3, 5 and 7:
for (int n : { 4, 2, 6, 1, 3, 5, 7 })
{
	t.insert(n);
}

// The following should print: 1234567
for (auto i = t.begin(Order); i != t.end(); i++)
{
	cout << *i;
}
```

Also ensure that your tree works with objects (including non-copyable objects!) as elements. Also as always, please ensure that your assignment submission is **your own individual work**.

You **may** use whatever parts of the STL are convenient in this assignment, but you **may not** simply build a collection of "nodes I need to visit" and copy that collection into your iterator. That is, your iterator must figure out, on every increment, **what the next node is, given where it currently is**. As always, if you’re not clear about anything, please ask!