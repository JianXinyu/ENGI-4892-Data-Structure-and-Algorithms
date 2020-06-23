Q: In Assignment1, why the declaration doesn't work? For example:

```c++
class List{
public:
    NodePtr p; // can't find NodePtr
private:
    class Node;
    using NodePtr = std::unique_ptr<int>
    
}
```



You can have a visibility label appear more than once within a class declaration, i.e., there is no “the `private` section”.

If the issue is that your declaration is depending on the existence of a `Node` class but you haven’t yet declared it in the source code, you can **add a forward declaration** (i.e., `class Node;`) earlier in the `List` class. That tells the compiler “there is a class called Node, don’t worry about the details yet, but you don’t need those to refer to an object of that type by pointer or reference.”

When you have a class member type (e.g., a field type or a method’s return or parameter type), the compiler needs to be aware that the type it’s referencing exists. To that extent, ordering matters. However, when you’re looking at the body of a method, the details of referenced types don’t need to appear before the code. So, ordering matters, and ordering doesn’t matter.