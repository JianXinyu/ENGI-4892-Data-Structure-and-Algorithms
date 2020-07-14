//
// Created by jianx on 7/13/2020.
//

#ifndef A2_BST_H
#define A2_BST_H
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
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <stack>

template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
private:
    struct Node
    {
        Node(T value) : element_(std::move(value))
        {
        }
        Node()
        {}
        void dot(std::ostream &o) const
        {
            // NOTE: this is slightly more complicated than strictly
            //       necessary (using addresses as names, etc.), but
            //       it will produce valid Dot output even when the
            //       node values are things like money (e.g., $17)

            o
                    << "  \"" << this << "\""
                    << " [ label = \"" << element_ << "\" ];\n";

            if (left_)
            {
                o
                        << "  \"" << this << "\""
                        << " -> "
                        << "\"" << left_.get() << "\""
                        << " [ label = \"L\" ]\n";

                left_->dot(o);
            }

            if (right_)
            {
                o
                        << "  \"" << this << "\""
                        << " -> "
                        << "\"" << right_.get() << "\""
                        << " [ label = \"R\" ]\n";

                right_->dot(o);
            }
        }

        T element_;
        std::shared_ptr<Node> left_;
        std::shared_ptr<Node> right_;
    };

    /**
     * Internal implementation of recursive insert.
     *
     * @param   value      the value to insert
     * @param   node       the root of the (sub-)tree being inserted into;
     *                     may be null if the (sub-)tree is empty
     */
    void insert(T &&value, std::shared_ptr<Node> &node)
    {
        if (not node)
        {
            node = std::make_shared<Node>(std::move(value));
        }
        else if (compare_(value, node->element_))
        {
            insert(std::move(value), node->left_);
        }
        else if (compare_(node->element_, value))
        {
            insert(std::move(value), node->right_);
        }
        else
        {
            // assuming no duplicates
        }
    }

    Comparator compare_;
    std::shared_ptr<Node> root_;
public:
    enum class Traversal
    {
        PreOrder,
        InOrder,
        PostOrder,
    };

    //! Insert a new value into the appropriate place in the tree.
    void insert(T value)
    {
        insert(std::move(value), root_);
    }

    void dot(std::ostream &o) const
    {
        o << "digraph {\n";

        if (root_)
        {
            root_->dot(o);
        }

        o << "}\n";
    }

    /**
     * An iterator that can traverse the BST in some order.
     *
     * The iterator contains a "current" node, a stack of parent nodes and
     * a Traversal value to remind it which strategy it's following.
     */
    class Iterator
    {
        //// especially for post order
        enum class NodeType
        {
            left,
            right,
            node,
        };
    public:
        // add whatever else you need here
        // Constructor
        explicit Iterator(std::shared_ptr<Node> node, Traversal type)
        {
            current_ = node;
            type_ = type;
            switch(type_)
            {
                case Traversal::PreOrder:
                {
                    // push right and left children of the popped node to stack
                    // Note: we push right first because we want to print left node first
                    if(current_->right_)
                    {
                        parents_.push(current_->right_);
                    }
                    if(current_->left_)
                    {
                        parents_.push(current_->left_);
                    }
                    break;
                }
                case Traversal::InOrder:
                {
                    // store all the left nodes into stack
                    while(current_->left_)
                    {
                        parents_.push(current_);
                        current_ = current_->left_;
                    }
                    break;
                }

                case Traversal::PostOrder:
                {
                    // find the first node, i.e. left-most node
                    post_helper_func();
                    break;
                }
            }
        };
        Iterator()
        {
        }

        /**
         * Move to the next node in the tree that should be accessed.
         *
         * This operator method just calls private methods to try and
         * keep the logic of the various traversal mechanisms clear.
         */
        const Iterator operator ++ (int)
        {
            if(type_ == Traversal::PreOrder)
            {
                // if there are nodes in stack
                if(!parents_.empty())
                {
                    // get the top node and pop it
                    current_ = parents_.top();
                    parents_.pop();
                    // push right and left children of the popped node to stack
                    // Note: we push right first because we want to print left node first
                    if(current_->right_)
                    {
                        parents_.push(current_->right_);
                    }
                    if(current_->left_)
                    {
                        parents_.push(current_->left_);
                    }
                }
                // otherwise, make current_ equal nullptr, i.e. end()
                else
                {
                    current_ = nullptr;
                }
            }
            else if(type_ == Traversal::InOrder)
            {
                // if current_ has right_ child, it means that
                // the node and its left subtree have been processed.
                // then process the right subtree.
                if(current_->right_)
                {
                    parents_.push(current_);
                    current_ = current_->right_;
                    // process the left branch of the subtree
                    while (current_->left_)
                    {
                        parents_.push(current_);
                        current_ = current_->left_;
                    }
                }

                // if current_ has no right_ child, it means that
                // the subtree has been processed, but which node is the root_ of this subtree hasn't been decided
                // How to decide this?
                // Note the parent node of current_ as pnode, the parent node of pnode as ppnode, and so on。
                // For example, if pnode doesn't exist, then the process is over.
                // if pnode exists, and current_ is the left child of pnode, then we need to process pnode.
                // if current_ is the right child of pnode, it means that at least the subtree with pnode as root_ has
                // been processed. We need to check ppnode now.
                // if ppnode doesn't exist, then no matter pnode is, the process is over.
                // if ppnode exists, and pnode is the left child of ppnode, then we need to process ppnode.
                // if pnode is the right child of ppnode, it means that at least the subtree with ppnode as root_ has
                // been processed. We need to check pppnode now.
                // Thus, the logic is clear. We need to go upward and check if pnode exists and whether current_ is the
                // right child of pnode. If both answers are yes, then we need to repeat this step.
                // Otherwise, we make current_ equal that node.
                else
                {
                    std::shared_ptr<Node> pNode = parents_.top();
                    parents_.pop();
                    while(pNode && current_ == pNode->right_)
                    {
                        current_ = pNode;
                        if(parents_.empty())
                        {
                            pNode = nullptr;
                        }
                        else{
                            pNode = parents_.top();
                            parents_.pop();
                        }
                    }
                    current_ = pNode;
                }
            }
            else if(type_ == Traversal::PostOrder)
            {
                if(!poststack_.empty())
                {
                    current_ = poststack_.top().first;
                    ntype_ = poststack_.top().second;
                    poststack_.pop();
                    post_helper_func();
                }
                else{
                    current_ = nullptr;
                }
            }
            return *this;
        };

        //! Dereference the iterator at its current position
        const T& operator * ()
        {
            return current_->element_;
        };

        //! Is this iterator *not* the same as another?
        bool operator != (const Iterator &other)
        {
            return current_ != other.current_;
        };

    private:
        // referred from https://www.geeksforgeeks.org/iterative-postorder-traversal-set-3/
        void post_helper_func()
        {
            while (ntype_!=NodeType::node)
            {
                if(current_ == nullptr)
                    continue;
                if(ntype_ == NodeType::left)
                {
                    poststack_.push(std::make_pair(current_, NodeType::right));
                    if(current_->left_)
                        poststack_.push(std::make_pair(current_->left_, NodeType::left));
                }
                else if(ntype_ == NodeType::right)
                {
                    poststack_.push(std::make_pair(current_, NodeType::node));
                    if(current_->right_)
                        poststack_.push(std::make_pair(current_->right_, NodeType::left));
                }
                current_ = poststack_.top().first;
                ntype_ = poststack_.top().second;
                poststack_.pop();
            }
        }
        std::shared_ptr<Node> current_;
        std::stack<std::shared_ptr<Node>> parents_;
        std::stack< std::pair< std::shared_ptr<Node>, NodeType> > poststack_; // especially for post order
        NodeType ntype_ = NodeType::left; // especially for post order
        Traversal type_;
    };

    /**
     * Returns an iterator that can be used to traverse the tree in the given order.
     *
     * This iterator should visit every node in the tree exactly once, after which
     * it should test equal to the iterator returned from `end()`.
     */
    Iterator begin(Traversal type)
    {
        return Iterator(root_, type);
    };

    /**
     * The end of a tree traversal.
     *
     * The iterator returned by this method should be usable as the end-of-iteration
     * marker for any iterator on this tree, whether it was traversing the tree in
     * pre-, in- or post-order.
     */
    Iterator end()
    {
        Iterator end;
        return end;
    };


};

#endif //A2_BST_H
