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

#include <cstdint>
#include <memory>

template<typename T>
class List
{
private:
    // Add whatever you need to add here
    class Node{
    public:
//        static NodePtr Create(Node *predecssor = nullptr)
        explicit Node(const T& object = T{},    Node *predecessor = nullptr,
                                                Node *successor = nullptr)
                : value_(object),   prev_(predecessor),
                                    next_(successor){}
        explicit Node(T&& object,   Node *predecessor = nullptr,
                                    Node *successor = nullptr)
                : value_(std::move(object)),    prev_(predecessor),
                                                next_(successor){}
        T       value_;
        Node    *prev_;
        Node    *next_;
    };

    Node    *head_;
    Node    *tail_;
    size_t  size_;

    void init()
    {
        size_ = 0;
        head_ = new Node;
        tail_ = new Node;
        head_->next_ = tail_;
        tail_->prev_ = head_;
    }

public:
    //! An iterator over the list
    class iterator
    {
        friend class List<T>;
    protected:
        Node *current_;
    public:
        iterator(Node *p = nullptr) : current_(p){};
        /**
         * The dereference operator.
         *
         * @returns   a reference to the "current" element
         */
        T& operator*()
        {
            return current_->value_;
        };

        /**
         * Pre-increment operator (i.e., `++i`).
         *
         * This method increments the iterator and then returns a
         * reference to the newly-incremented iterator.
         *
         * @returns   a reference to this iterator, after incrementing
         */
        iterator& operator++()
        {
            current_ = current_->next_;
            return *this;
        };

        /**
         * Post-increment operator (i.e., `i++`).
         *
         * This method returns a copy of this iterator as it currently
         * is (i.e., pointing where it currently points) and _then_
         * increments itself.
         *
         * @param     ignored   this is only used to distinguish the two
         *                      increment operators (pre- and post-)
         *                      from each other: its value should be
         *                      ignored
         *
         * @returns   an iterator to the previously-current element
         */
        iterator operator++(int ignored)
        {
            iterator old = *this;
            ++( *this );
            return old;
        };

        //! Is this iterator pointing at the same place as another one?
        bool operator== (const iterator& rhs) const
        {
            return current_ == rhs.current_;
        };

        //! Is this iterator pointing at a different place from another?
        bool operator!= (const iterator& rhs) const
        {
            return current_ != rhs.current_;
        };
    };

    //! Default constructor
    List()
    { init(); };

    //! Copy constructor
    List(const List& rhs)
    {
        init();
        for(auto x : rhs )
            this->push_back( x );
    };

    //! Move constructor

    List(List&& rhs)
    : size_(rhs.size_), head_(rhs.head_), tail_(rhs.tail_)
    {
        rhs.size_ = 0;
        rhs.head_ = new Node;
// why using the following instead the above can't pass the
// move construction test, raising segmentation fault? Using
// above, I got error on my compiler, whit exit code -1073740940 (0xC0000374)
//        rhs.head_ = nullptr;
//        rhs.tail_ = nullptr;
    };

    //! Destructor
    ~List()
    {
        while( !empty() )
            {erase( begin() );}
        delete head_;
        delete tail_;
    };

    //! Copy assignment operator
    List& operator= (const List& rhs)
    {
        List copy = rhs;
        std::swap( *this, copy);
        return *this;
    };

    //! Move assignment operator
    List& operator= (List&& rhs)
    {
        std::swap(size_, rhs.size_);
        std::swap(head_, rhs.head_);
        std::swap(tail_, rhs.tail_);

        return *this;
    };

    //
    // Accessors:
    //
    //! How many elements are in this list?
    size_t size() const
        { return size_; }

    //! Is this list empty?
    bool empty() const
        { return size_==0; }

    //! Get an iterator to the beginning of the list
    iterator begin() const
        { return iterator(head_->next_); }

    //! Get an iterator just past the end of the list
    iterator end() const
        { return iterator(tail_);}


    //
    // Mutators:
    //
    //! Copy an element to the front of the list
    void push_front(const T& x)
        { insert( begin(), x); }

    //! Move an element to the front of the list
    void push_front(T&& x)
        { insert( begin(), std::move(x));}

    //! Copy an element to the back of the list
    void push_back(const T& x)
        { insert( end(), x);}

    //! Add an element to the back of the list
    void push_back(T&& x)
        { insert( end(), std::move(x));}

    /**
     * Copy an element into an arbitrary location.
     *
     * This method makes a copy of an element and inserts that copy into a
     * location pointed at by the given iterator. After insertion into a
     * list of n elements, the list should contain n+1 elements (i.e., no
     * existing element should be replaced).
     *
     * @returns   an iterator pointing at the newly-inserted element
     */
    iterator insert(iterator itr, const T& object)
    {
        Node *p = itr.current_;
        Node *newNode = new Node(object, p->prev_, p);
        p->prev_->next_ = newNode;
        p->prev_ = newNode;
        size_++;

        return iterator(newNode);
    };

    /**
     * Move an element into an arbitrary location.
     *
     * This method inserts an element into a location pointed at by the
     * given iterator, using move semantics to avoid copies. After insertion
     * into a list of n elements, the list should contain n+1 elements
     * (i.e., no existing element should be replaced).
     *
     * @returns   an iterator pointing at the newly-inserted element
     */
    iterator insert(iterator itr, T&& object)
    {
        Node *p = itr.current_;
        Node *newNode = new Node(std::move(object), p->prev_, p);
        p->prev_->next_ = newNode;
        p->prev_ = newNode;
        size_++;

        return iterator(newNode);
    }

    //! Remove an element from an arbitrary location
    void erase(iterator itr)
    {
        Node *p = itr.current_;
        p->prev_->next_ = p->next_;
        p->next_->prev_ = p->prev_;
        delete p;
        --size_;
    }

};
