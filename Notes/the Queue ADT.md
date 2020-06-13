## Stack

### Postfix Expressions

我们正常使用的数学计算式成为中缀表达式(infix expression)，比如 $1+2+3*4$ 。常见的科学计算器计算的结果都是15，因为考虑了运算优先级，相当于自动加上了括号。但是早期简单的计算器只会按顺序无脑计算，计算结果变成24。所以我们应想办法用顺序的表达式来实现这样的计算(evaluate)顺序：计算1+2的和记为A1，计算3*4记为A2，将A1+A2，最后将其和存在A1。据此我们将表达式写为：$1 \quad 2 + 3 \quad 4 * +$ 。 这种表达式成为后缀表达式(postfix expression)，又称为Reverse Polish Notation(RPN)。

用Stack最容易evaluate RPN:

- 看到数(operand)时，push into stack;
- 看到运算(operator)符时，把最后两个数从stack中pop出来计算，再将计算结果push into stack。

the time to evaluate a postfix expression is $O(N)$，because processing each element in the input consists of stack operations and therefore takes constant time.

pros of postfix expression: 不需要知道任何先验规则，诸如运算优先级。

### Infix to Postfix Conversion

stack不仅可以用来计算后缀表达式(evaluate a **postfix** expression)，也可以用来将中缀(**infix**)表达式转为后缀。

为方便阐述，我们只考虑+、*。 

- infix expression: $a+b*c+(d*e+f)*g$

- postfix expression: $a\quad b\quad c *  + d\quad e* f+g*+$

  （空格只用于区分不同的数）

  步骤如下：

  1. 读到operand时，立即放入output
  2. 读到operator和左括号时，先放到一个stack里
  3. 如果读到右括号，pop the stack, writing symbols until we encounter a corresponding left parenthesis, which is popped but not output. 如果读到其他symbol，如+、-、(，then we pop entries from the stack until we find an entry of lower priority.  One exception is that we never remove a ( from the stack except when processing a ). For the purposes of this operation, + has lowest priority and **( highest**. When the popping is done, we push the operator onto the stack.
  4. Finally, if we read the end of input, we pop the stack until it is empty, writing symbols
     onto the output.

## Queue

就像stack，queue也是list。 但与stack不同的是，queue在一端插入，却在另一端删除。

queue的基本操作有:

- enqueue: inserts an element at the end of the list (called the rear)
- dequeue: deletes (and returns) the element at the start of the list (called the front)

