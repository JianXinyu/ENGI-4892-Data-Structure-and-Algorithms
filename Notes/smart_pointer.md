本人愚钝，cplusplus.com的描述及各种问答网站上关于智能指针的回答实在不好理解，幸而发现了这个解释，通俗易懂，总结如下。
Referred and Concluded from YouTuber [CppNuts](https://www.youtube.com/watch?v=wUzn0HljjRE&list=PLk6CEY9XxSIAI2K-sxrKzzSyT6UZR5ObP). 

## Introduction
Smart pointer is a **class** which wraps a raw pointer, to manage the life time of the pointer. 以下例子可以方便理解，即使不写delete sp, 在执行完main后也会自动调用destructor.
```cpp
#include <iostream>

class smartPtr
{
public:
    explicit smartPtr(int *ptr = nullptr)
    {
        data = ptr;
    }
    ~smartPtr()
    {
        std::cout << "delete pointer \n";
        delete data;
    }
private:
    int *data;
};

int main()
{
  int *ptr(new int(10));
  smartPtr sp(ptr);
  return 0;
}
```

The most fundamental job of smart pointer is to remove the chance of memory leak. It makes sure that the object is deleted if it is not reference any more.

Smart pointer has three types:
1. unique_ptr: allows only one owner of the underlying pointer
2. shared_ptr allows multiple owners of the same pointer (Reference count is maintained)
3. week_ptr is a special typy of shared_ptr which doesn't count the reference

## unique_ptr
unique_ptr is a class template. It wraps a raw pointer and de-allocates this raw pointer when **unique_ptr object goes out of scope**, even if when exception comes out in the other part of code. Similar to actual pointers, we can use -> and * on the unique_ptr object, because they've already been overloaded. 
unique_ptr has following methods: get, release, reset, swap, get_deleter(TODO)
且看下面的例子
```cpp
#include <iostream>
#include <memory>
class Foo
{
public:
    explicit Foo(int value): x{value} {}
    ~Foo() {std::cout << "Foo is destroyed! \n";}
    int get() {return x;}
private:
    int x;
};

int main()
{
    Foo* f = new Foo(42);
//    std::unique_ptr<Foo> f(new Foo(42));
//    std::unique_ptr<Foo> f = std::make_unique<Foo>(20);
    std::cout << f->get() << (*f).get() << std::endl; // both ways work
    
    return 0;
}
```
并不会删除f， 导致了f指向的地址泄露。 若将f定义换成 `std::unique_ptr<Foo> f(new Foo(42));`，便会发现自动调用了destructor。还可以采用第二种更好的定义方法: `make_unique`。
unique_ptr 不能用于copy ownership，只能move ownership，将一个object的ownership转移到另一个unique_ptr上。 这也是unique的含义。
```cpp
std::unique_ptr<Foo> p1 = std::make_unique<Foo>(24);
std::unique_ptr<Foo> p2 = std::make_unique<Foo>(42);
// std::unique_ptr<Foo> p3 = p1; //ERROR
std::unique_ptr<Foo> p3 = std::move(p1); // move ownership, p1 becomes nullptr
```
get()仅仅返回unique_ptr所指向的内容，不会对unique_ptr产生任何影响。p2.get返回的是Foo(20)，p是指向Foo(20)的一个普通指针。
release()与get()类似，但会将unique_ptr变成nullptr。
reset()可以重设unique_ptr指向的object, 而先前的unique_ptr则被删除。
swap()交换两个unique_ptr指向的objects。
```cpp
Foo* p4 = p2.get();	//p2不受影响
std::cout << p4->get(); //输出42
Foo* p5 = p2.release(); //p2变为nullptr
p3.reset(p4); //由指向Foo(24)变为Foo(42)
std::unique_ptr<Foo> p6 = std::make_unique<Foo>(24);
swap(p3, p6); //p3指向Foo(24), p6指向Foo(42)
```
reset()可以理解为两步：第一步删除原来的，第二布定义新的。所以下面的代码可以输出两遍"Foo is destroyed!"。
```cpp
int main()
{
    Foo* f = new Foo(42);
    std::unique_ptr<Foo> p = std::make_unique<Foo>(24);
    p.reset(f); //由指向Foo(24)变为Foo(42)
    return 0;
}
```