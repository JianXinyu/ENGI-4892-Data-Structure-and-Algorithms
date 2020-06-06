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
    void append(T data)
    {
        Node *tmp = new Node(data);
        //if the list is empty, head_ and tail_ will be the same node
        if(head_ == nullptr)
        {
            head_ = tmp;
            tail_ = tmp;
        }
        else //add the node at the end of the linked list
        {
            tail_->next_ = tmp;
            tail_ = tail_->next_;
        }
    }

    //display contents of linked list
    void display()
    {
        Node *pnode = head_; //present node
        while(pnode != nullptr) {
            std::cout << pnode->value_ << "-->";
            pnode = pnode->next_;
        }
        std::cout << "Null \n";
    }

private:
    class Node
    {
    public:
        explicit Node(T value)
            : value_(value), next_(nullptr)
        {
        }

        T      value_;
        Node   *next_;
    };
    Node       *head_;
    Node       *tail_;
};

int main() {
    //test integer
    LinkedList<int> listInt;
    listInt.append(1);
    listInt.append(2);
    std::cout << "Int Linked List: ";
    listInt.display();

    //test double
    LinkedList<double> listDbl;
    listDbl.append(1.1);
    listDbl.append(2.2);
    std::cout << "Double Linked List: ";
    listDbl.display();

    //test string
    LinkedList<std::string> listStr;
    listStr.append("Alice");
    listStr.append("Bob");
    std::cout << "String Linked List: ";
    listStr.display();

    //test non-copyable type
    LinkedList<std::unique_ptr<double>> listNC;
    double a = 1.1, b = 2.2;
    std::unique_ptr<double> ptr_a(&a), ptr_b(&b);
    listNC.append(std::move(ptr_a));



   return 0;
}


