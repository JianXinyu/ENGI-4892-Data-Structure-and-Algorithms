#include <iostream>
#include <memory>
#include <cassert>

//overload operator << to print reference of std::unique_ptr
template <typename T>
std::ostream& operator << (std::ostream &os, const  std::unique_ptr<T> &uniquePtr)
{
    os << *uniquePtr;
    return os;
}

template< typename T>
class LinkedList
{
public:
    //! construct an empty linked list
    LinkedList()
    {
        //Creat sentinel nodes for the beginning and end of the list
        head_ = Node::Create();

        auto tail = Node::Create(head_.get());
        tail_ = tail.get();
        head_->append(std::move(tail));
    }

    //add a new node at the end of the linked list
    LinkedList& operator << (T rhs)
    {
        // Find the last node that isn't the end sentinel
        Node *last = tail_->prev();

        // Creat the new node to be inserted before the end
        auto n = Node::Create(last);
        n->setValue(std::move(rhs));

        // Steal the end iterator, give ownership to the new node
        n->append(std::move(last->takeNext()));

        //Append the new node after the previously-last node
        last->append(std::move(n));

        // with sentinel, we don't need to check special case
//        auto tmp = std::make_unique<Node>(std::move(x));
//        //check whether its the first node
//        if(tail_)
//        {
//            tail_->append(std::move(tmp));
//            tail_ = tail_->next();
//        }
//        else
//        {
//            head_ = std::move(tmp);
//            tail_ = head_.get();
//        }

        //operators usually need to return reference to something
        //returning *this can chain cascade usages
        //e.g. someList << 1 << 2 << 3;
        return *this;
    }

    /**
     * Retrieve a reference to the first element in the list.
     *
     * @pre    the list should not be empty
     */
    T& front()
    {
        assert(head_->next() != tail_ && "called front() on empty list");
        return **head_->next();
    }

    /**
     * Retrieve a reference to the last element in the list.
     *
     * @pre    the list should not be empty
     */
    T& back()
    {
        assert(head_->next() != tail_ && "called back() on empty list");
        return **tail_->prev();
    }

    /**
     * Display all elements in linked list.
     *
     * @pre    the list should not be empty
     */
    void display()
    {
        assert(head_->next() != tail_ && "called back() on empty list");

        Node *pnode = head_.get(); //present node
        pnode = pnode->next_.get();

        //keep printing node until the tail_
        while(pnode && pnode != tail_){
            std::cout << pnode->value_ << "-->";
            pnode = pnode->next_.get();
        }
        std::cout << "Null \n";
    }

private:
    //
    // NodePtr will be more convenient to use than std::unique_ptr<Node>.
    // We can creat this new type name with typedef or using, but first we
    // need to forward-declare the Node type
    //
    class Node;
    using NodePtr = std::unique_ptr<Node>;

    class Node
    {
    public:
        static NodePtr Create(Node *predecessor = nullptr)
        {
            return std::make_unique<Node>(predecessor);
        }

        Node(Node *predecessor = nullptr)
            : next_(nullptr), prev_(predecessor)
        {
        }

        void setValue(T value)
        {
            value_ = std::move(value);
        }
        /**
         * Append a node as the "next" node from this one
         * @param n new node
         */
        void append(NodePtr n)
        {
            //TODO what if we have a next pointer?
            next_ = std::move(n);
            next_->prev_ = this;
        }

        Node* next()
        {
            return next_.get();
        }

        Node* prev()
        {
            return prev_;
        }

        /**
         * Steal this node's "next" node
         */
         NodePtr takeNext()
        {
             return std::move(next_);
        }

        /**
         * Dereference operator: get this node's value.
         * @pre node is not a sentinel
         */
         T& operator* ()
        {
             return value_;
        }

        /**
         * Compare operator: compare this node to another by value
         */
         bool operator < (const Node &other)
        {
             return value_ < other.value_;
        }

        T                           value_;
        NodePtr                      next_;
        Node                        *prev_;
    };
    NodePtr                          head_;
    Node                            *tail_;
};

using namespace std;
int main() {
    //test integer
    LinkedList<int> listInt;
    listInt << 1 << 2;
    std::cout << "Int Linked List: ";
    listInt.display();

    //test double
    LinkedList<double> listDbl;
    listDbl << 1.1 << 2.2;
    std::cout << "Double Linked List: ";
    listDbl.display();

    //test string
    LinkedList<std::string> listStr;
    listStr << "Alice" << "Bob";
    std::cout << "String Linked List: ";
    listStr.display();

    //test non-copyable type
    LinkedList<std::unique_ptr<double>> pointers;
    pointers << std::make_unique<double>(1.1) << std::make_unique<double>(2.2);
    std::cout << "Unique Pointer Linked List: ";
    pointers.display();

//    LinkedList<double> numbers;
//    numbers << 3.1415 << 2 << 42;
//
//    cout << "front of numbers: " << numbers.front() << endl;
//    cout << "back of numbers: " << numbers.back() << endl;
//
//    LinkedList<unique_ptr<double>> pointers;
//    pointers << make_unique<double>(3.14);

   return 0;
}


