The *special member functions* are class (or struct) member functions that, in certain cases, the compiler automatically generates for you. 

These functions are:

1. default constructor
2. destructor
3. copy constructor
4. copy assignment operator
5. move constructor
6. move assignment operator

If your class does not define one or more of the special member functions, then the compiler may implicitly declare and define the functions that are used. The compiler-generated implementations are called the *default* special member functions. The compiler does not generate functions if they are not needed.

You can explicitly declare a default special member function by using the **= default** keyword. This causes the compiler to define the function only if needed, in the same way as if the function was not declared at all.

In some cases, the compiler may generate *deleted* special member functions, which are not defined and therefore not callable. This can happen in cases where a call to a particular special member function on a class doesn't make sense, given other properties of the class. To explicitly prevent automatic generation of a special member function, you can declare it as deleted by using the **= delete** keyword.

The compiler generates a *default constructor*, a constructor that takes no arguments, only when you have not declared any other constructor. If you have declared only a constructor that takes parameters, code that attempts to call a default constructor causes the compiler to produce an error message. The compiler-generated default constructor performs simple member-wise [default initialization](https://docs.microsoft.com/en-us/cpp/cpp/initializers?view=vs-2019#default_initialization) of the object. Default initialization leaves all member variables in an indeterminate state.

The default destructor performs member-wise destruction of the object. It is virtual only if a base class destructor is virtual.

The default copy and move construction and assignment operations perform member-wise bit-pattern copies or moves of non-static data members. Move operations are only generated when no destructor or move or copy operations are declared. A default copy constructor is only generated when no copy constructor is declared. It is implicitly deleted if a move operation is declared. A default copy assignment operator is generated only when no copy assignment operator is explicitly declared. It is implicitly deleted if a move operation is declared.

## Constructor

在创建类的新对象时执行