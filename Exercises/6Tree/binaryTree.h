//
// Created by jianx on 6/29/2020.
//

#ifndef TREE_BINARYTREE_H
#define TREE_BINARYTREE_H

#include <iostream>
#include <memory>
#include <functional>

enum TreeTraversalOrder
{
    PreOrder,
    PostOrder,
    InOrder,
};

template <typename T>
class BinaryTree
{
public:
    void traverse(TreeTraversalOrder order, std::function<void (const T&)> func)
    {
        if(root_)
        {
            root_->traverse(order, func);
        }
    }
    BinaryTree& setRoot(T value)
    {
        root_ = std::make_unique<Node>(std::move(value));
        return *this;
    }
    /**
     * @pre the root, if it exists, does not already have a left
     *      and  a right child
     */
    BinaryTree& addChild(T value)
    {
        auto node = std::make_unique<Node>(std::move(value));
        if(not root_)
        {
            root_ = std::move(node);
        }
        else if(not root_->left_)
        {
            root_->left_ = std::move(node);
        }
        else if(not root_->right_)
        {
            root_->right_ = std::move(node);
        }
        else
        {
//            assert(false && "tree is already full");
        }
        return *this;
    }

    BinaryTree& operator << (T value)
    {
        addChild(value);

        return *this;
    }

private:
    struct Node
    {
        Node(T value)
                : value_(value)
        {
        }

        void traverse(TreeTraversalOrder order,
                      std::function<void (const T&)> func)
        {
            // we can use switch, or
            if(order == TreeTraversalOrder::PreOrder)
            {
                func(value_);
            }

            if(left_)
            {
                left_->traverse(order, func);
            }

            if(order == TreeTraversalOrder::InOrder)
            {
                func(value_);
            }

            if(right_)
            {
                right_->traverse(order, func);
            }

            if(order == TreeTraversalOrder::PostOrder)
            {
                func(value_);
            }
        }

        T value_;
        std::unique_ptr<Node> left_;
        std::unique_ptr<Node> right_;
    };

    std::unique_ptr<Node> root_;
};

static void printInteger(const int &n)
{
    std::cout << n << std::endl;
}

static size_t nodeCount;

template <typename T>
void countNodes(const T&)
{
    nodeCount++;
}

#endif //TREE_BINARYTREE_H
