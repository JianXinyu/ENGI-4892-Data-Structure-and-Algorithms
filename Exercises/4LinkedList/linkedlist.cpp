#include <iostream>
#include <memory>
#include <list>
#include <vector>

template< typename T>
class LinkedList
{
public:
    //constructor
    LinkedList()
            : head_(nullptr), tail_(nullptr)
    {
    }

    //add a new node at the end of the linked list
    LinkedList& operator << (T x)
    {
        auto tmp = std::make_unique<Node>(std::move(x));
        //check whether its the first node
        if(tail_)
        {
            tail_->append(std::move(tmp));
            tail_ = tail_->next();
        }
        else
        {
            head_ = std::move(tmp);
            tail_ = head_.get();
        }
        //operators usually need to return reference to something
        //returning *this makes cascade usage possible
        //e.g. someList << 1 << 2 << 3;
        return *this;
    }

    //display contents of linked list
    void display()
    {
        Node *pnode = head_.get(); //present node
        //keep printing node until the tail_

        while(pnode) {
            std::cout << *pnode->value_ << "-->";
            pnode = pnode->next_.get();
        }
        std::cout << "Null \n";
    }

private:
    class Node
    {
    public:
        Node(T value)
            : next_(nullptr), prev_(nullptr)
        {
            value_ = std::move(value);
        }

        void append(std::unique_ptr<Node> n)
        {
            next_ = std::move(n);
            next_->prev_ = this;
        }

        Node* next()
        {
            return next_.get();
        }

        T                           value_;
        std::unique_ptr<Node>       next_;
        Node                        *prev_;
    };
    std::unique_ptr<Node>           head_;
    Node                            *tail_;
};

//template <typename T>
//std::ostream& operator<<(std::ostream &os, const  LinkedList<std::unique_ptr<T>> &list)
//{
//
//}
int main() {
//    //test integer
//    LinkedList<int> listInt;
//    listInt << 1 << 2;
//    std::cout << "Int Linked List: ";
//    listInt.display();
//
//    //test double
//    LinkedList<double> listDbl;
//    listDbl << 1.1 << 2.2;
//    std::cout << "Double Linked List: ";
//    listDbl.display();
//
//    //test string
//    LinkedList<std::string> listStr;
//    listStr << "Alice" << "Bob";
//    std::cout << "String Linked List: ";
//    listStr.display();

    //test non-copyable type
    LinkedList<std::unique_ptr<double>> pointers;
    pointers << std::make_unique<double>(1.1) << std::make_unique<double>(2.2);
    std::cout << "Unique Pointer Linked List: ";
    pointers.display();

   return 0;
}


