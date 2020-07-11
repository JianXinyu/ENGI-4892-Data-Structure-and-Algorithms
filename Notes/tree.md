Each node in a tree has a depth and height.

**Depth**: length of the path from the tree's root to the node

**Height**: longest length of the path  from the node to a leaf.

The height of a tree, or the depth of the tree, is the height of its root.

**Balanced**: if the heights of each node's subtrees are equal, or at least close, we call  the tree balanced.  A balanced tree has **logarithmic height**: the length of the path from the root to any node in the tree is $O(log n)$.

# BINARY SEARCH TREES

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
   1. find the node by recursive descent



### Adelson–Velsky–Landis (AVL) tree

a binary search tree that keeps itself balanced when you add or remove nodes. **Self-balanced**

Problem: BST works well when it is balanced, $O(log_2 n)$. adding or removing nodes will cause BST loses its balance. Worst case: degenerate into a linked list, $O(n)$.

Solution:  add one more constraint to keep the tree self-balanced.

- binary

   - each node's left subtree and right subtree are partitioned by the node's value

   - **New**: every node's height can differ in height by no more than one

     ​			Each node's balance factor: the difference between the heights of the node's two subtrees

     ![image-20200711091052011](.\figures\avl)

#### Single Rotation

​	--- newly-inserted nodes are ***outer*** nodes, since they appear on the outside edge of a subtree.

		- add a node to the left of the left subtree of a node
		- add a node to the right of the right subtree of a node

**Without child**

![image-20200711091430456](.\figures\image-20200711091430456.png)

1. decide which of 17's subtrees has the greater value. In this case, the left subtrees

2. take the left subtree and make it the root of the subtree that used to be rooted at 17

3. make the old root of the subtree, i.e., 17, the right child of the new subtree root, i.e., 8

   ![image-20200711092231893](.\figures\image-20200711092231893.png)

**With child**

Insert 2 to the tree

![image-20200711093804127](.\figures\image-20200711093804127.png)

the new subtree root (4) *already has* a child node on its right: the 5 node.

![image-20200711095833215](.\figures\image-20200711095833215.png)

the right child(5) of the new subtree root(4) becomes the left subchild of the old subtree root(6)



#### Double rotation

Insert an ***inner*** node, that is, the right child of a left node or the left child of a right node

![image-20200711110113460](.\figures\image-20200711110113460.png)

1. arrange for the subtree to be too deep in an outer node rather than an inner one through rotation.

   in this case, left rotation

   ![image-20200711110207139](.\figures\image-20200711110207139.png)

2. rotate. in this case, right rotation

   ![image-20200711110421013](.\figures\image-20200711110421013.png)



the **complexity** of performing this double-rebalancing in terms of the number of nodes in the tree:

