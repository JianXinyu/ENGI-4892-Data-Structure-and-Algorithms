Each node in a tree has a depth and height.

**Depth**: length of the path from the tree's root to the node

**Height**: longest length of the path  from the node to a leaf.

The height of a tree, or the depth of the tree, is the height of its root.

**Balanced**: if the heights of each node's subtrees are equal, or at least close, we call  the tree balanced.  A balanced tree has **logarithmic height**: the length of the path from the root to any node in the tree is $O(log n)$.

# BINARY SEARCH TREES

## BINARY SEARCH TREES

### Binary tree

Binary tree is a specialization of the general tree concept. It's node has 0, 1 or 2 children.

Thus, the representation of tree could be optimized: each node only has two child pointers, called **left** and **right**. With this representation, we can do in-order traversal.

**Traversal**: To traverse any node, first traverse its left subtree recursively, then visit the node in question, then traverse its right subtree recursively

### Binary search tree

Specialize a binary tree by adding an ordering constraint on the nodes, we end up with the ubiquitous *binary search tree*. In a binary search tree, every node has the property that values smaller than its own are in its left subtree and values larger than its own are in its right subtree. This means that every subtree within the tree is sorted; 

Visualization: https://visualgo.net/en/bst

1. **search**: since sorted, search faster than linearly. there are no false starts and the maximum number of recursions is equal to the height of the tree, which in a balanced tree is $O(logn)$.

   ![image-20200704162617810](figures\image-20200704162617810.png)

   Find 24: 

   ```C++
   if this == null
       return null
   else if this key == search value
       return this
   else if this key < search value
       search right
   else search left
   ```

   

2. **Finding** the minimum or maximum value: straight forward, just keep following left or right

3. **insertion**:  
   1. start from root, compare the new value to the current node's value 
   2. if less than the node value, insert on the left
   3. if bigger than the node value, insert on the right
   4. if equal, increment a counter in the node, add the new value to a linked list hung off the node or (in some cases) simply ignore the new value
      - adding to an empty tree is a matter of creating a new node and setting the subtree’s "root" to point at it.
      - in a balanced tree, insertion takes logarithmic time. However, insertion may cause the tree to become less balanced.

![image-20200704163048782](figures\image-20200704163048782.png)

```c++
if insertion point is found
	creat new vertex
if value to be inserted < this key
	go left
else go right
```

4. **Removal**
   1. find the node