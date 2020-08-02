template <typename T>
class  Set{
private:
    class Node;
    class iterator{
    private:
        Node *current;
        friend class Set;
    public:
         iterator(Node *p):current(p){}
         iterator():current(nullptr){}
         const T operator*() const
         {
             return current->data;
         }
         iterator & operator++()
         {
             current = current->right;
             return *this;
         }
         iterator & operator++(int)
         {
             iterator old = *this;
             current = current->right;
             return old;
         }
         bool operator==(const iterator &rhs) const
         {
             if (current == rhs.current)
             {
                 return true;
             }
             else
             {
                 return false;
             }
         }
         bool operator!=(const iterator &rhs) const
         {
             if (!(operator==(rhs)))
             {
                 return true;
             }
             else
             {
                 return false;
             }
         }

    };

    class Node{
    private:
        T data;
        Node *left;
        Node *right;
        Node(T a, Node *p1 = nullptr,Node *p2 = nullptr):data(a),left(p1),right(p2){}

        friend class Set;
        friend class iterator;
    };
    iterator begin( Node *& tep) const
        {
            if (tep->left != nullptr)
            {
                begin(tep->left);
            }
            else
            {
                return iterator(tep);
            }
        }
    iterator end( Node *& tep) const
        {
            if ( tep->right != nullptr)
            {
                end(tep->right);
            }
            else
            {
                iterator(tep->right);
            }
        }
    const iterator find( Node* & tep,const T & a) const
    {
        if (tep != nullptr)
        {
             if (a < tep->data)
            {
                find(tep->left,a);
            }
            else if (tep->data < a)
            {
                find(tep->right,a);
            }
            else
            {
                return iterator(tep);
            }
        }
        else
        {
            return iterator(nullptr);
        }

    }
    Node * insert( Node * & tep,const T & x) const
    {
        if (tep == nullptr)
        {
            return tep = new Node(x,nullptr,nullptr);
        }
        else if (x < tep->data)
        {
            return insert(tep->left, x);
        }
        else if(tep->data < x)
        {
            return insert(tep->right,x);
        }
        else
        {
            ;
        }
    }
    Node * clone(Node * & t) const
    {
        if (t == nullptr)
            return nullptr;
        return new Node(t->data,clone(t->left),clone(t->right));
    }
    void makeEmpty(Node * & t)
    {
        if ( t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }
    Node * findmin(Node * & tep) const
    {
        if (tep == nullptr)
        {
            return nullptr;
        }
        else if (tep->left == nullptr)
        {
            return tep;
        }
        else
        {
            findmin(tep->left);
        }

    }
    Node * findmax(Node * & tep) const
    {
        if (tep == nullptr)
        {
            return nullptr;
        }
        else if (tep->right == nullptr)
        {
            return tep;
        }
        else
        {
            findmin(tep->right);
        }

    }
    Node * erase(Node * & tep,const  T & x)
    {
            if (tep == nullptr)
            {
                return nullptr;
            }
            else if (x < tep->data)
            {
                erase(tep->left,x);
            }
            else if(tep->data < x)
            {
                erase(tep->right,x);
            }
            else if(tep->left != nullptr && tep->right != nullptr)
            {
                tep->data = findmin(tep->right)->data;
                erase(tep->right,tep->data);
                return tep;
            }
            else
            {
                Node * oldNode = tep;
                if (tep->left != nullptr)
                    tep = tep->left;
                else
                    tep = tep->right;

                delete oldNode;
                return tep;
            }

    }

private:

    Node *root;

public:
    void makeEmpty()
    {
        makeEmpty(root);
    }
    Set(Node * p = nullptr):root(p){}
    Set(const Set & rhs)
    {
        root = rhs.root;
    }
    const Set & operator=( Set & rhs)
    {
        if(this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }
    ~Set()
    {
        makeEmpty();
    }
    iterator begin()
    {
        if(root != nullptr)
        {
            begin(root);
        }

    }
    iterator end()
    {
        end();
    }
    iterator find(const T & a)
    {
      return  find(root,a);
    }
    iterator insert(const T & x)
    {
        return iterator(insert(root,x));
    }
    iterator erase(const T x)
    {
        return iterator(erase(root,x));
    }

};