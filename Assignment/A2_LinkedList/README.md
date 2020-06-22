Implement a singly-linked list.

Complete the class template that you find in [List.h](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/assignment/1/List.h). In particular, you will need to implement methods for the class templates `List<T>` and `List<T>::iterator`. You can choose how to manage memory (manually or via smart pointers), but don’t use any STL data structures or algorithms other than smart pointers without checking with me.

You should sketch a design for your data type and submit a class diagram (which may be hand-sketched or drawn in a diagramming tool) as an image file within your `assignments/1` directory. You will then need to implement methods in (at least) three class templates and submit your code in a file called `assignments/1/List.h`.

Further details on the semantics of each method are given in the header file [List.h](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/assignment/1/List.h) itself. If you’re not clear about anything, please ask!

## Within `List<T>`

### The "big five"

(plus the default constructor)

|           SIGNATURE            |       DESCRIPTION        |
| :----------------------------: | :----------------------: |
|            `List()`            |   Default constructor    |
|      `List(const List&)`       |     Copy constructor     |
|         `List(List&&)`         |     Move constructor     |
|           `~List()`            |        Destructor        |
| `List& operator=(const List&)` | Copy assignment operator |
|   `List& operator=(List&&)`    | Move assignment operator |

### Accessors:

|       SIGNATURE       |          DESCRIPTION           |
| :-------------------: | :----------------------------: |
| `size_t size() const` | Number of elements in the list |
| `bool empty() const`  |       Is the list empty?       |
|  `iterator begin()`   |      Beginning iteration       |
|   `iterator end()`    |        Ending iteration        |

### Mutators:

|               SIGNATURE               |                 DESCRIPTION                  |
| :-----------------------------------: | :------------------------------------------: |
|      `void push_front(const T&)`      |   Copy an element to the front of the list   |
|        `void push_front(T&&)`         |   Move an element to the front of the list   |
|      `void push_back(const T&)`       |   Copy an element to the back of the list    |
|         `void push_back(T&&)`         |    Add an element to the back of the list    |
| `iterator insert(iterator, const T&)` |  Copy an element into an arbitrary location  |
| `iterator insert(iterator, const T&)` |  Move an element into an arbitrary location  |
|        `void erase(iterator)`         | Remove an element from an arbitrary location |

## Within `List<T>::iterator`:

|         SIGNATURE          |       DESCRIPTION       | USAGE |
| :------------------------: | :---------------------: | :---: |
|        `iterator()`        |       Constructor       |       |
|      `T& operator*()`      |  Dereference operator   | `*i`  |
|  `iterator& operator++()`  | Pre-increment operator  | `++i` |
| `iterator operator++(int)` | Post-increment operator | `i++` |