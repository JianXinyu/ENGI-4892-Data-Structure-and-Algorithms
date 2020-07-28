/*
 * Copyright 2020 Jonathan Anderson
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

#ifndef SET_H_
#define SET_H_

#include <memory>
#include <stack>
#include <utility>

template<typename T>
struct Node
{
    explicit Node(T &&value) : element_(std::move(value))
    { }

    const T& value() const { return element_; }

    //! check if the tree contains the value
    bool contains(const T& value) const
    {   // if value < node value, go to left and check if left is null
        if(value < element_)
        {
            return left_ and left_->contains(std::move(value));
        }
            // if value > node value, go to right and check if right is null
        else if(value > element_)
        {
            return right_ and right_->contains(std::move(value));
        }
            // otherwise value == element_, the tree contains the value
        else{
            return true;
        }
    };

    T element_;
    std::shared_ptr<Node> left_ = nullptr;
    std::shared_ptr<Node> right_ = nullptr;
};

template<typename T>
class rawIterator
{
public:
    rawIterator() : current_(nullptr) {}
    explicit rawIterator(const std::shared_ptr<Node<T>> &node) : current_(node)
    {
        if(current_)
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
        }
        else{

        }
    }

    rawIterator(const rawIterator<T> &other) : current_(other.current_), parents_(other.parents_)
    {
    }

    //! Move to the next iterator
//    rawIterator operator ++ (int)
//    {
//        if(current_ == end_)
//        {
//            return *this;
//        }
//        // if there are nodes in stack
//        if(!parents_.empty())
//        {
//            // get the top node and pop it
//            current_ = parents_.top();
//            parents_.pop();
//            // push right and left children of the popped node to stack
//            // Note: we push right first because we want to print left node first
//            if(current_->right_)
//            {
//                parents_.push(current_->right_);
//            }
//            if(current_->left_)
//            {
//                parents_.push(current_->left_);
//            }
//        }
//            // otherwise, make current_ equal nullptr, i.e. end()
//        else
//        {
//            current_ = nullptr;
//        }
//        return *this;
//    }

    rawIterator operator ++()
    {
        if(current_ == end_)
        {
            return *this;
        }
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
        return *this;
    };
    rawIterator operator ++ (int)
    {
        rawIterator<T> old = *this;
        if(current_ == end_)
        {
            return old;
        }
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
        return old;
    }
    //! Dereference the iterator at its current position
//    const T& operator * ()
//    {
//        return current_->element_;
//    };

    const T& operator * () const
    {
        return current_->element_;
    };

    //! Is this iterator *not* the same as another?
    bool operator == (const rawIterator &other)
    {
        return current_ == other.current_;
    };

    //! Is this iterator *not* the different as another?
    bool operator != (const rawIterator &other)
    {
        return current_ != other.current_;
    };

    bool operator != (const rawIterator &other) const
    {
        return current_ != other.current_;
    };

    rawIterator takeEnd()
    {
        current_ = end_;
        return *this;
    }

//    rawIterator find ( const T& value, std::shared_ptr<Node> &node )
//    {
//        if(!node)
//        {
//            return rawIterator();
//        }
//        else
//        {
//            if(value < node->value())
//            {
//                find(std::move(value), node->left_);
//            }
//            else if(value > node->value())
//            {
//                find(std::move(value), node->right_);
//            }
//            else
//            {
//                return rawIterator(node);
//            }
//        }
//    }
    rawIterator find ( const T& value)
    {
        if(!current_)
        {
            return rawIterator<T>();
        }
        else
        {
            if(value < current_->value())
            {
                rawIterator next(current_->left_);
                next.find(std::move(value));
            }
            else if(value > current_->value())
            {
                rawIterator next(current_->right_);
                next.find(std::move(value));
            }
            else
            {
                return rawIterator<T>(current_);
            }
        }
    }
private:
    std::shared_ptr<Node<T>> current_;
    std::shared_ptr<Node<T>> end_ = nullptr;
    std::stack<std::shared_ptr<Node<T>>> parents_;
};
/**
 * A set that holds values, ignoring duplicates.
 */
template<typename T>
class Set
{
public:
    typedef rawIterator<T> Iterator;
    typedef rawIterator<T> ConstIterator;

    //! Add an element to this set.
    void insert(T value)
    {
        insert(std::move(value), root_);
    };

    //! Is a specified element already in the set?
    bool contains(const T& value) const
    {
        return (not empty() and root_->contains(std::move(value)));
    };

    //! How many values are in this set?
    size_t size() const
    {
        return count_;
    };

    // Iterators over const and non-const sets:
    Iterator begin()
    {
        Iterator beginIter(root_);
        return beginIter;
    };
    ConstIterator begin() const
    {
        ConstIterator beginIter(root_);
        return beginIter;
    };

    Iterator end()
    {
//        Iterator endIter(root_);
//        endIter.takeEnd();
        Iterator endIter;
        return endIter;
    };
    ConstIterator end() const
    {
        ConstIterator endIter(root_);
        endIter.takeEnd();
        return endIter;
    };

    /**
     * Look up a specific value within this set.
     *
     * This should return an iterator that is equal to end() if the value
     * is not found.
     */
    Iterator find(const T& value)
    {
        if(!contains(value))
        {
            Iterator nullIter;
            return nullIter;
        }
        Iterator beginIter(root_);
        return beginIter.find(std::move(value));
    };
    ConstIterator find(const T& value) const
    {
        ConstIterator beginIter(root_);
        return beginIter.find(std::move(value));
    };




private:


    //! Is this tree empty?
    bool empty() const
    {
        return (not root_);
    }

    /**
     * Internal implementation of recursive insert.
     *
     * @param   value      the value to insert
     * @param   node       the root of the (sub-)tree being inserted into;
     *                     may be null if the (sub-)tree is empty
     */
    void insert(T &&value, std::shared_ptr<Node<T>> &node)
    {
        // if node is null, set the value to this node, and return
        if(!node)
        {
            node.reset(new Node<T>(std::move(value)));
            count_ = 1;
            return;
        }
        //if node is not null
        //if inserted value < node value, go to left
        if(value < node->value())
        {
            insert(std::move(value), node->left_);
        }
            //if inserted value > node value, go to right
        else if(value > node->value())
        {
            insert(std::move(value), node->right_);
        }

        count_++;
    };


    size_t count_ = 0;
    std::shared_ptr<Node<T>> root_= nullptr;
};

#endif