//
// Created by jianx on 7/6/2020.
//

#ifndef BST_BST_H
#define BST_BST_H
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

#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <iostream>
template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
public:
    //! Does this tree contain the given value?
    bool contains(const T &value)
    {
        return (not empty() and root_->contains(value));
    }

    size_t maxDepth() const
    {
        if (empty())
        {
            return 0;
        }

        return root_->maxDepth();
    }

    //! Is this tree empty?
    bool empty() const
    {
        return (not root_);
    }

    //! Insert a new value into the appropriate place in the tree.
    void insert(T value)
    {
        insert(std::move(value), root_);
    }

    /**
     * Find the minimum value in the tree.
     *
     * @pre   tree is not empty
     */
    const T& min() const
    {
        assert(root_);
        return root_->min().value();
    }

    /**
     * Find the minimum value in the tree.
     *
     * @pre   tree is not empty
     */
    const T& max() const
    {
        assert(root_);
        return root_->max().value();
    }

    /**
     * Remove a value (if it exists) from the tree.
     *
     * @returns   whether or not anything was found to remove
     */
    bool remove(const T &&value)
    {
        return remove(value, root_);
    }

    /**
     * Print all values of the tree
     * @param func  print function
     */
     void print(std::ostream &func)
    {
        print(func, root_, 0);
    }
//another implementation of print
//    const BinarySearchTree& print(std::ostream &out) const
//    {
//         if(root_)
//         {
//             root_->print(out);
//         }
//         return *this;
//     }

     /**
	 * Output this tree in a GraphViz DOT representation as a
	 * directed graph ("digraph").
	 *
	 * Calls to this method will cause an entire graph (starting
	 * with "digraph G {") to be output to the given std::ostream.
	 *
	 * @param   o    the output stream to write to
	 */
    void printDot(std::ostream &out) const
     {
        out << "digraph G{ \n";
        root_->printDot(out);
        out << "} \n";
     };

    //! rotate the tree to the left
    void rotate()
    {
        if(!empty())
        {
            rotateWithLeftChild(root_);
        }
    }

private:

    struct Node
    {
        // Did you know that structs can have methods too?
        Node(T &&value)
                : element_(value), count_(1)
        {
        }

        const T& value() const { return element_; }

        //! check if the tree contains the value
        bool contains(const T& value) const
        {   // if value < node value, go to left and check if left is null
            if(value < element_)
            {
                return left_ and left_->contains(value);
            }
            // if value > node value, go to right and check if right is null
            else if(value > element_)
            {
                return right_ and right_->contains(value);
            }
            // otherwise value == element_, the tree contains the value
            else{
                return true;
            }
        };

        // implementation of min() and max() are trivial. Since the binary tree is sorted,
        // we can go all the way following left or right.
        Node& min()
        {
            if(!left_)
            {
                return *this;
            }
            return left_->min();
        };
        Node& max()
        {
            if(!right_)
            {
                return *this;
            }
            return right_->min();
        };
// another implementation of print
//        const Node& print(std::ostream &out) const
//        {
//            if(left_)
//            {
//                left_->print(out);
//            }
//            out<<element_<<"x"<<count_<<std::endl;
//            if(right_)
//            {
//                right_->print(out);
//            }
//
//            return *this;
//        }


        /**
         * Output information about this node in GraphViz DOT format.
         *
         * This will output information about this node
         * (with no graph-level decorations such as "digraph G {")
         * and recursively descend to its children.
         */
        void printDot(std::ostream& out) const
        {
            out << "  " << element_ << " [ label = \"count " << count_
                << ", value " << element_ << "\" ];\n";
            if(left_)
            {
                out << "  " << element_ << " -> " << left_->element_ << " [ label = \"L\" ]; \n";
            }
            if(right_)
            {
                out << "  " << element_ << " -> " << right_->element_ << " [ label = \"R\" ]; \n";
            }

            if(left_)
            {
                left_->printDot(out);
            }

            if(right_)
            {
                right_->printDot(out);
            }
        };

        //! return the minimum value of the tree
        T takeMin()
        {
            if (left_)
            {
                return left_->takeMin();
            }
            return std::move(element_);
        }

        //! return the maximum depth of the tree
        size_t maxDepth() const
        {
            if(!this)
            {
                return 0;
            }
            else {
                // recurse for each side
                size_t LDepth = left_->maxDepth();
                size_t RDepth = right_->maxDepth();
                // return bigger one
                return (LDepth > RDepth) ? (LDepth+1) : (RDepth+1);
            }
        }

        T element_;
        size_t count_;
        std::unique_ptr<Node> left_;
        std::unique_ptr<Node> right_;
    };

    /**
     * Internal implementation of recursive insert.
     *
     * @param   value      the value to insert
     * @param   node       the root of the (sub-)tree being inserted into;
     *                     may be null if the (sub-)tree is empty
     */
    void insert(T &&value, std::unique_ptr<Node> &node)
    {
        // if node is null, set the value to this node, and return
        if(!node)
        {
            node.reset(new Node(std::move(value)));
            return;
        }
        //if node is not null
        //if inserted value < node value, go to left
        if(value < node->value())
        {
            insert(std::move(value), node->left_);
        }
        //if inserted value > node value, go to right
        else if(value > node->value())
        {
            insert(std::move(value), node->right_);
        }
        //if equal, increase count_
        else if(value == node->value())
        {
            node->count_++;
        }
    };

    /**
     * Internal implementation of recursive removal.
     *
     * @param   value      the value to remove
     * @param   node       the root of the (sub-)tree being inserted into;
     *                     may be null if the (sub-)tree is empty
     */
    bool remove(const T &value, std::unique_ptr<Node> &node)
    {
        if(!node)
        {
            // end of the line: we didn't find the value!
            return false;
        }
        else if (value < node->element_) // value < node value
        {
            return remove(value, node->left_); // recurse left
        }
        else if(value > node->element_) // value > node value
        {
            return remove(value, node->right_); // recurse right
        }
        else if(node->left_ and node->right_)
        {
            // this is the node we want to remove, and we have two children
            // to deal with... this is a special case

            // Get the inorder successor (smallest in the right subtree)
            // Copy the inorder successor's content to this node
            node->element_ = node->right_->takeMin();
            // remove the inorder successor node
            return remove(node->element_, node->right_);
        }
        else{
            // this is the right node and we have at most one child
            // update the pointer to skip straight to the child
            node.swap(node->left_ ? node->left_ : node->right_);
            return true;
        }
    };

    /**
     * Print the whole tree
     * @param func      print function
     * @param node      current print node
     * @param indent    number of spaces to be printed before the node value
     */
    void print(std::ostream &func, std::unique_ptr<Node> &node, int indent = 0)
    {
        // if node is null, print is over
        if(!node){return;}
        // print indentation
        for(int i=0; i<indent; ++i)
        {
            printf(" ");
        }
        // print node value using customized function
        func << node->value();
        printf("\n");
        // recursively print children
        print(func, node->left_, indent+1);
        print(func, node->right_, indent+1);
    }

    using NodePtr = std::unique_ptr<Node>;
    /**
     * Rotate binary tree node with left child.
     * Referred from the textbook Page 156
     *          k2                     k1
     *    k1          Z   -->     X          k2
     *  X    Y                            Y      Z
     */
    void rotateWithLeftChild( NodePtr & k2 )
    {
        NodePtr k1 = std::move(k2->left_);
        k2->left_ = std::move(k1->right_);
        k1->right_ = std::move(k2);
        k2 = std::move(k1);
    }

    Comparator compare_;
    std::unique_ptr<Node> root_;
};

template<typename T, typename Comparator = std::less<T>>
class AVL
{
public:
    //! Insert a new value into the appropriate place in the tree.
    void insert(T value)
    {
        insert(std::move(value), root_);
    }

    /**
     * Print all values of the tree
     * @param func  print function
     */
    void print(std::ostream &func)
    {
        print(func, root_, 0);
    }

private:
    struct AvlNode
    {
        T   element_;
        int height_;
        int count_;
        std::unique_ptr<AvlNode> left_;
        std::unique_ptr<AvlNode> right_;

        AvlNode( const T & ele,  int h = 0 )
                : element_{ ele }, height_{ h }, count_{1}
                { }

        AvlNode( T && ele,  int h = 0 )
                : element_{ std::move( ele ) },  height_{ h }, count_{1}
                { }

        const T& value() const { return element_; }
    };

    void insert(T value, std::unique_ptr<AvlNode> & node)
    {
        // if node is null, set the value to this node, and return
        if(!node)
        {
            node.reset(new AvlNode(std::move(value)));
            return;
        }
        //if node is not null
        //if inserted value < node value, go to left
        if(value < node->value())
        {
            insert(std::move(value), node->left_);
        }
            //if inserted value > node value, go to right
        else if(value > node->value())
        {
            insert(std::move(value), node->right_);
        }
            //if equal, increase count_
        else if(value == node->value())
        {
            node->count_++;
        }
        balance(node);
    }

    void balance(std::unique_ptr<AvlNode> &node)
    {
        if(!node)
            return;

        if( height( node->left_ ) - height( node->right_ ) > 1 )
        {
            if( height( node->left_->left_ ) >= height( node->left_->right_ ) )
                rotateWithLeftChild( node );

        }

        else if( height( node->right_ ) - height( node->left_ ) > 1 )
        {

            if( height( node->right_->right_ ) >= height( node->right_->left_ ) )
                rotateWithRightChild( node );

        }

        node->height_ = std::max( height( node->left_ ), height( node->right_ ) ) + 1;
    }

    int height( std::unique_ptr<AvlNode> &node ) const
    {
        return !node? -1 : node->height_;
    }

    /**
     * Rotate binary tree node with left child.
     * update heights, then set new root.
     * Referred from the textbook Page 156
     *          k2                     k1
     *    k1          Z   -->     X          k2
     *  X    Y                            Y      Z
     */
    void rotateWithLeftChild( std::unique_ptr<AvlNode> & k2 )
    {
        int k2lh = height( k2->left_ ); // k2 left_ height_
        std::unique_ptr<AvlNode> k1 = std::move(k2->left_);
        k2->left_ = std::move(k1->right_);
        k2->height_ = std::max( k2lh, height( k2->right_ ) ) + 1;
        k1->right_ = std::move(k2);
        k1->height_ = std::max( height( k1->left_ ), k1->right_->height_ ) + 1;
        k2 = std::move(k1);
    }

    /**
     * Rotate binary tree node with right child.
     * update heights, then set new root.
     * Referred from the textbook Page 156
     *         k1                           k2
     *    X          k2        -->     k1        Z
     *            Y      Z          X      Y
     */
    void rotateWithRightChild( std::unique_ptr<AvlNode> & k1 )
    {
        int k1rh = height(k1->right_); // k1 right_ height_
        std::unique_ptr<AvlNode> k2 = std::move(k1->right_);
        k1->right_ = std::move(k2->left_);
        k1->height_ = std::max( height( k1->left_ ), k1rh ) + 1;
        k2->left_ = std::move(k1);
        k2->height_ = std::max( height( k2->right_ ), k2->left_->height_ ) + 1;
        std::cout << height(k2->right_) << std::endl;
        k1 = std::move(k2);
    }

    void print(std::ostream &func, std::unique_ptr<AvlNode> &node, int indent = 0)
    {
        // if node is null, print is over
        if(!node){return;}
        // print indentation
        for(int i=0; i<indent; ++i)
        {
            printf(" ");
        }
        // print node value using customized function
        func << node->value();
        printf("\n");
        // recursively print children
        print(func, node->left_, indent+2);
        print(func, node->right_, indent+2);
    }

    std::unique_ptr<AvlNode> root_;
};

#endif //BST_BST_H
