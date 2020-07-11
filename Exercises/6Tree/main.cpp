#include "BST.h"

#include <iostream>

int main()
{
	BinarySearchTree<int> bst;

	bst.insert(4);
	bst.insert(5);
	bst.insert(7);
    bst.insert(6);
    bst.insert(2);
    bst.insert(1);
    bst.insert(9);
	std::cout << "min value: " << bst.min() << "\n";
	std::cout << "max value: " << bst.max() << "\n";

	bst.print(std::cout);


	for(int i = 0; i <= 10; i++)
    {
	    std::cout << "bst " << (bst.contains(i)? "does " : "doesn't ")
	            <<"contain the value " << i << "\n";
    }

	std::cout << "Max Depth: " << bst.maxDepth() << "\n";

	std::cout << "Remove 4:" << bst.remove(4) << "\n";
    bst.print(std::cout);

    bst.printDot(std::cout);

    // Exercises for 10 Jul Q1, test rotate
    std::cout << "test tree rotation: \n";
    bst.rotate();
    bst.printDot(std::cout);

    // Exercises for 10 Jul Q2, test AVL balance
    std::cout<< "test AVL balance \nOriginal tree: \n";
    AVL<int> avl;
    avl.insert(49);
    avl.insert(17);
    avl.insert(71);
    avl.insert(8);
    avl.print(std::cout);

    std::cout << "test AVL left case \n";
    avl.insert(4);
    avl.print(std::cout);

    std::cout << "test AVL right case \n";
    avl.insert(72);
    avl.insert(73);
    avl.print(std::cout);
	return 0;
}
