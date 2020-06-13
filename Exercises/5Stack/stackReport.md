## Exercises for 10 Jun 2020

1. Demonstrate that the stack used to store C++ functions' local variables grows downwards.

   - A stack is a LIFO data structure that accepts new elements on its logical "top" and return them from the same place. It only provides the operation of pushing a new element onto the stack and pop an element off of the stack.  

   - Growing downwards means that the computer allocate the stack memory starts from high addresses and grows down. We can demonstrate it in the following code:

```c++
#include <iostream>
int main()
{
    int a = 1;
    int b = 2;
    int c = 3;

    std::cout << "Address of a: " << &a << '\n';
    std::cout << "Address of b: " << &b << '\n';
    std::cout << "Address of c: " << &c << '\n';
}
```

The output is :

```
Address of a: 0x61fe1c
Address of b: 0x61fe18
Address of c: 0x61fe14
```

Clearly, the memory address is getting smaller.

2. The [reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) (RPN) is a notation for expressing mathematical operations without requiring parentheses. Unlike infix notation (e.g., 1+21+2), calculations can be done in a single pass through the token stream — no additional parsing is required. Write a function that accepts a pair of iterators over a container of strings (e.g., `{ "1", "2", "+", "3", "*" }`) and that returns an integer derived from an RPN interpretation of the strings (in the example above, 9).

   Pseudo code: referred from the [link](https://www.tutorialspoint.com/evaluate-reverse-polish-notation-in-cplusplus-program)

   ```
   for each character ch in the postfix expression, do
       if ch is an operator ☉, then
           a := pop first element from stack,
           b := pop second element from the stack
           res := b ☉ a
           push res into the stack
       else if ch is an operand, then
           add ch into the stack
       return element of stack top
   ```

   see code at mathExpression.cpp

3. [optional] Use Dijkstra’s stack-based [shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm) to convert an infix mathematical expression (e.g., 1+2×(3+4)1+2×(3+4)) to a postfix/RPN expression (e.g., `3 4 + 2 * 1 +`).

The shunting-yard algorithm is a method for parsing mathematical expressions written in infix notation to Reverse Polish Notation(RPN).

The logic is as followings:

1. if read operand, add it into output
2. if read operator and left parenthesis，put it into a stack
3. If read right parenthesis, pop the stack, writing symbols until we encounter a corresponding left parenthesis, which is popped but not output. If encounter with other symbol, such as +、-、(，then we pop entries from the stack until we find an entry of lower priority.  One exception is that we never remove a ( from the stack except when processing a ). For the purposes of this operation, + has lowest priority and **( highest**. When the popping is done, we push the operator onto the stack.
4. Finally, if we read the end of input, we pop the stack until it is empty, writing symbols
   onto the output.

see code at mathExpression.cpp



## Exercises for 12 Jun 2018

1. Implement a template queue class using a `std::list` field. Provide `enqueue()`, `dequeue()` and `size()` methods — no iterators required.

   see class Queue at queque.cpp

2. Write a C++ program that accepts user input via `std::cin` and, depending on that input, enqueues and dequeues values of type `int`. For example, you might accept user commands like `enqueue NUMBER` to enqueue a value in your queue and `dequeue` to dequeue a number and print it out. Your program should refuse to dequeue a number when the queue is empty.

   see main() at queque.cpp