Pointer types

For C++11:

Reference types: allow us to define a new name for an existing value

- rvalue reference
- lvalue reference

to figure out what they are, we need to think about the concept of lvalues and rvalues.

## lvalues and rvalues

Note that the precise rules are complex, and we provide a general description.

Consider example:

```c++
vector<string> arr( 3 );
const int x = 2;
int y;
int z = x + y;
string str = "foo";
vector<string> *ptr = &arr;
```



- lvalue: an expression that identifies a non-temporary object. If you have a name for a variable, it is an lvalue, regardless of whether it is modifiable. `arr, str, arr[x], &x, y, z, ptr, *ptr, (*ptr)[x], x` 
- rvalue: an expression that identifies a temporary object or is a value (such as a literal constant) not associated with any object. literal: ` 2, "foo"` temporary:` x+y, str.substr(0,1)` 

some cases in which the result of a function call or operator call can be an lvalue: `*ptr, arr[x], cin>>x>>y`,

others where it can be an rvalue. Intuitively, if the function call computes an expression whose value doesn't exist prior to the call and doesn't exit once the call is finished unless it is copied somewhere, it is likely to be an rvalue.

## reference type

Now. let's see what is reference type. In C++11, we can have two types of references: lvalue references and rvalue references.

- an **lvalue reference** is declared by placing an & after some type. It then becomes a synonym for the object it references. 

```C++
string str = "hell";
string & rstr = str; 				// rstr is another name for str
rstr += ’o’; 						// changes str to "hello"
bool cond = (&str == &rstr);		// true; str and rstr are same object
string & bad1 = "hello";			// illegal: "hello" is not a modifiable lvalue
string & bad2 = str + "";			// illegal: str+"" is not an lvalue
string & sub = str.substr( 0, 4 ); 	// illegal: str.substr( 0, 4 ) is not an lvalue
```

- an **rvalue reference** is declared by placing an && after some type. An rvalue reference has the same characteristics as an lvalue reference except that, unlike an lvalue reference, an rvalue reference can also reference an rvalue (i.e., a temporary).

```c++
string str = "hell";
string && bad1 = "hello";			// Legal
string && bad2 = str + "";			// Legal
string && sub = str.substr( 0, 4 ); // Legal
```

Usage:

Whereas lvalue references have several clear uses in C++, the utility of rvalue references is not obvious. 

- lvalue:
  - aliasing complicated names
  - range for loops
  - avoiding a copy































