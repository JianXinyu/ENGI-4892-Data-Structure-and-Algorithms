#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <list>


template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
public:
    struct Node
    {
        Node(T value) : element_(std::move(value))
        {
        }
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
        std::unique_ptr<Node> left_;
        std::unique_ptr<Node> right_;
    };


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
    public:
        //make the current pointer NULL
        Iterator() : Curr_Node {nullptr}{

        }
        //check to see the traversal method passed as arguement and call the respective method
        Iterator(Node* ptr, Traversal order_) : root(ptr),traversal_method(order_){
            //list to hold the node pointers in the proper order
            std::list<Node*> ordered_tree;
            if (ptr != NULL)
            {
                if (order_==Traversal::InOrder)
                {
                    TraverseInOrder(ptr,ordered_tree);
                }
                if (order_==Traversal::PreOrder)
                {
                    TraversePreOrder(ptr, ordered_tree);
                }
                if (order_ == Traversal::PostOrder)
                {
                    TraversePostOrder(ptr, ordered_tree);
                }
            }
            //call the constructor to set the current pointer to NULL
            else Iterator();
            //once the pointers have been pushed to the list, set the current pointer to point to the first node
            Curr_Node = ordered_tree.front();
        }

        /**
         * Move to the next node in the tree that should be accessed.
         *
         * This operator method just calls private methods to try and
         * keep the logic of the various traversal mechanisms clear.
         */
        Iterator operator ++ (const int)
        {
            //create a list to hold the ordered nodes
            std::list<Node*> list_;
            if (traversal_method == Traversal::InOrder)
            {
                TraverseInOrder(root, list_);
            }
            if (traversal_method == Traversal::PreOrder)
            {
                TraversePreOrder(root, list_);
            }
            if (traversal_method == Traversal::PostOrder)
            {
                TraversePostOrder(root, list_);
            }
            //if the iterator and the current node is pointing to the same node, then traverse the iterator
            for (auto itr = list_.begin(); itr != list_.end(); itr++)
            {
                if (*itr == Curr_Node)
                {
                    itr++;
                    // check to see if the iterator is pointing to the end of the list
                    if (itr == list_.end())
                    {
                        Curr_Node = NULL;
                        return *this;
                    }
                    //once the iterator is pointing to the correct next node, set the current node to the new(iterator) position and return the pointer
                    Curr_Node = *itr;
                }
            }
            return *this;
        }

        //! Dereference the iterator at its current position
        const T& operator * (){

            return Curr_Node->element_;
        }

        //! Is this iterator *not* the same as another?
        bool operator != (const Iterator &other){
            return (Curr_Node != other.Curr_Node);
        }

        // add whatever else you need here
        //stores the method of traversal
        Traversal traversal_method;
        // nodes to hold the root node and the current node that the obejct is pointing to
        Node* root;
        Node* Curr_Node;



    private:
        //the methods of ordering the tree in the specified way are listed below:
        void TraverseInOrder(Node* ptr, std::list<Node*>& list)
        {
            if (ptr == NULL){return;}
            else
            {
                if (ptr->left_!= NULL)
                {
                    TraverseInOrder(ptr->left_.get(), list);
                }
                list.push_back(ptr);
                if (ptr->right_)
                {
                    TraverseInOrder(ptr->right_.get(), list);

                }
            }


        }
        void TraversePreOrder(Node* ptr, std::list<Node*>& list)
        {
            if (ptr == NULL){return;}
            else
            {
                list.push_back(ptr);
                if (ptr->left_)
                {
                    TraversePreOrder(ptr->left_.get(), list);
                }
                if (ptr->right_)
                {
                    TraversePreOrder(ptr->right_.get(), list);

                }

            }

        }
        void TraversePostOrder(Node* ptr, std::list<Node*>& list)
        {
            if (ptr == NULL){return;}
            else
            {
                if (ptr->left_!= NULL)
                {
                    TraversePostOrder(ptr->left_.get(), list);
                }
                if (ptr->right_)
                {
                    TraversePostOrder(ptr->right_.get(), list);

                }
                list.push_back(ptr);
            }
        }

    };
    //overloads the constructor by passing arguments. Returns an iterator pointing to the first node
    Iterator begin (Traversal order)
    {
        return Iterator(root_.get(), order);
    }
    Iterator end(){
        // returns the iterator at the end of the list
        return Iterator();
    }


private:



    /**
     * Internal implementation of recursive insert.
     *
     * @param   value      the value to insert
     * @param   node       the root of the (sub-)tree being inserted into;
     *                     may be null if the (sub-)tree is empty
     */
    void insert(T &&value, std::unique_ptr<Node> &node)
    {
        if (not node)
        {
            node = std::make_unique<Node>(std::move(value));
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
    std::unique_ptr<Node> root_;

};




