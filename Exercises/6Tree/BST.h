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
private:
    struct Node
    {
        // Did you know that structs can have methods too?
        Node(T &&value)
                : element_(value), count_(1)
        {
        }

        const T& value() const { return element_; }

        bool contains(const T&) const;
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
        T takeMin();
        size_t maxDepth() const;

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
    bool remove(const T &value, std::unique_ptr<Node> &node);

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

    Comparator compare_;
    std::unique_ptr<Node> root_;
};
#endif //BST_BST_H
