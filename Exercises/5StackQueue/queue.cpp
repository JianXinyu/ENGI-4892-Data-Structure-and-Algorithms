#include <iostream>
#include <list>

template <typename T>
class Queue
{
public:
    void enqueue(T value)
    {
        std::cout << "Enqueue: " << value << '\n';
        queue_.push_back(value);
    }

    void dequeue()
    {
        if(!queue_.empty())
        {
            std::cout << "Dequeue: " << queue_.front() << '\n';
            queue_.pop_front();
        }
        else
            std::cout << "Queue is empty!" << '\n';
    }

    int size()
    {
        return queue_.size();
    }

private:
    std::list<T> queue_;
};
int main() {
    Queue<int> q;

    std::string cmd;
    int value;
    while(true)
    {
        std::cout << "Please Enter (enqueue, dequeue or esc): ";
        std::cin >> cmd;

        if(cmd == "esc"){
            break;
        }
        else if(cmd == "enqueue") {
            std::cout << "Please enter an integer: ";
            std::cin >> value;
            q.enqueue(value);
        }
        else if(cmd == "dequeue"){
            q.dequeue();
        }

    }
    return 0;
}
