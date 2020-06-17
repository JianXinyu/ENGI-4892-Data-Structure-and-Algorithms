#include <iostream>
#include <string>
#include <vector>
#include <memory>

template <typename T>
class Tree
{
public:
    Tree() : root_(nullptr)
    {
    }

    void addNode(T s)
    {
        auto node = std::make_unique<Node>(s);

        if(not root_)
        {
            root_ = std::move(node);
        }
        else{
            root_->addChild(std::move(node));
        }
    }

    /**
     * Set the value of the tree's root node.
     */
    Tree& setRoot(T value)
    {
        root_->setValue(value);
        return *this;
    }

    /**
     * Add a leaf node to the top level of this tree.
     */
    Tree& addChild(T value)
    {
        std::unique_ptr<Node> leaf = std::make_unique<Node>(value);
        root_->addChild(std::move(leaf));
        return *this;
    }

    /**
     * Add a subtree to the top level of this tree, using move
     * semantics to "steal" the subtree's nodes.
     */
    Tree& addSubtree(Tree<T>&& subtree)
    {
        root_->addChild(std::move(subtree.root_));
        return *this;
    }

private:
    class Node
    {
    public:
        Node(T s)
                : value_(std::move(s))
        {
        }

        void setValue(T value)
        {
            value_ = value;
        }

        void addChild(std::unique_ptr<Node> child)
        {
            children_.push_back(std::move(child));
        }


    private:
        T value_;
        std::vector<std::unique_ptr<Node>> children_;
    };

    std::unique_ptr<Node> root_;
};
int main() {

    Tree<std::string> tree;
    tree.addNode("42");
    tree.addNode("the meaning of life!");
    tree.setRoot("24");
    tree.addChild("new child");

    Tree<std::string> tree2;
    tree2.addNode("I'm sub.");
    tree2.addChild("I'm the first born.");
    tree2.addChild("I'm the second born.");
    tree.addSubtree(std::move(tree2));

    return 0;
}
