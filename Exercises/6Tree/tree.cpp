#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>

template <typename T>
class Tree
{
    class Node;
    using treeNode = std::unique_ptr<Node>;
public:
    Tree() : root_(nullptr)
    {
    }

    void addNode(T s)
    {
        auto node = std::make_unique<Node>(s);

        if(not root_){
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
        treeNode leaf = std::make_unique<Node>(value);
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
    
    void visitPreorder(std::function<void (const T&)> func)
    {
        if(root_){
            root_->preorder(func);
        }
    }

    void visitPostorder(std::function<void (const T&)> func)
    {
        if(root_){
            root_->postorder(func);
        }
    }

private:
    class Node
    {
    public:
        explicit Node(T s)
                : value_(std::move(s)), child_(nullptr), sibling_(nullptr)
        {
        }

        void setValue(T value)
        {
            value_ = value;
        }

        void addChild(treeNode child)
        {
            // original one
//            children_.push_back(std::move(child));
            // if child_ is nullptr, make child_ point to the first of its children
            if(not child_){
                child_ = std::move(child);
            }
            // else, add the sibling to the child_
            else {
                child_->addSibling(std::move(child));
            }
        }

        void addSibling(treeNode child)
        {
            // if sibling_ is nullptr, make it point to the new child
            if(not sibling_){
                sibling_ = std::move(child);
            }
            // else, switch to the sibling_ until the last sibling_(nullptr)
            else{
                sibling_->addSibling(std::move(child));
            }
        }

        //! pre-order traversal, we visit a node before visiting its children
        void preorder(std::function<void (const T&)> func)
        {
            func(value_);
            if(child_){
                child_->preorder(func);
            }
            if(sibling_){
                sibling_->preorder(func);
            }
        }
        //! post-order traversal, we visit a node’s children before visiting the node itself.
        void postorder(std::function<void (const T&)> func)
        {

            if(child_){
                child_->postorder(func);
            }
            func(value_);
            if(sibling_){
                sibling_->postorder(func);
            }
        }

    private:
        T value_;
        treeNode child_;
        treeNode sibling_;
//        std::vector<std::unique_ptr<Node>> children_;
    };

    treeNode root_;
};

template <typename T>
void visit(const T &value)
{
    static size_t i = 0;
    std::cout << "Node " << i++ << ": " << value << "\n";
}


int main() {

    Tree<std::string> tree;
    tree.addNode("42"); // initialize the root
    tree.addNode("the meaning of life!"); // add the first node the the root
    tree.setRoot("24"); // reset the root_ value

    tree.addChild("new child"); // add a leaf node to the root

    // initialize another tree
    Tree<std::string> tree2;
    tree2.addNode("I'm subtree.");
    tree2.addChild("I'm the first born.");
    tree2.addChild("I'm the second born.");

    tree.addSubtree(std::move(tree2)); // add a subtree to the root

    // the tree now is:
    /* 24
     *      the meaning of life!
     *      new child
     *      I'm subtree.
     *          I'm the first born.
     *          I'm the second born.
     */

    std::cout << "Pre-order: \n";
    tree.visitPreorder(visit<std::string>);

    std::cout << "Post-order: \n";
    tree.visitPostorder(visit<std::string>);
    return 0;
}

