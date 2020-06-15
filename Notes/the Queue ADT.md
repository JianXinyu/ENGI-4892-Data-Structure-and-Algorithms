## Stack

### Postfix Expressions

我们正常使用的数学计算式成为中缀表达式(infix expression)，比如 $1+2+3*4$ 。常见的科学计算器计算的结果都是15，因为考虑了运算优先级，相当于自动加上了括号。但是早期简单的计算器只会按顺序无脑计算，计算结果变成24。所以我们应想办法用顺序的表达式来实现这样的计算(evaluate)顺序：计算1+2的和记为A1，计算3*4记为A2，将A1+A2，最后将其和存在A1。据此我们将表达式写为：$1 \quad 2 + 3 \quad 4 * +$ 。 这种表达式成为后缀表达式(postfix expression)，又称为Reverse Polish Notation(RPN)。

用Stack最容易evaluate RPN:

- 看到数(operand)时，push into stack;
- 看到运算(operator)符时，把最后两个数从stack中pop出来计算，再将计算结果push into stack。

the time to evaluate a postfix expression is $O(N)$，because processing each element in the input consists of stack operations and therefore takes constant time.

pros of postfix expression: 不需要知道任何先验规则，诸如运算优先级。

下面给出实现:

```C++
/**
 * conduct operation
 * @param a, b: operands
 * @param oper: operator
 * @return calculation result
 * if the operator is wrong, return negative infinity
 */
float calculation(float a, float b, char oper)
{
    if(oper == '+')
        return a + b;
    else if(oper == '-')
        return a - b;
    else if(oper == '*')
        return a * b;
    else if(oper == '/')
        return a / b;
    else if(oper == '^')
        return std::pow(a, b);
    else
        return INT_MIN;
}

/**
 * calculate a postfix expression using reverse Polish notation (RPN)
 * Logic:   find numbers and store in the stack;
 *          find operand, conduct calculation and store the result
 * @param iterators
 * @return calculation result
 */
float RPN(const std::vector<std::string> &expr)
{
    std::stack<float> numPool;
    for(const auto& i : expr)
    {
        char ch = i[0];
        //if operand
        if(ch >= '0' && ch <= '9')
        {
            //store the number
            numPool.push(float(ch - '0'));
        }
        //if operator
        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        {
            //get and delete the last number
            float num2 = numPool.top();
            numPool.pop();
            //get and delete the second last number
            float num1 = numPool.top();
            numPool.pop();
            //store the result
            numPool.push(calculation(num1, num2, ch));
        }
    }

    return numPool.top();
}

int main()
{
    std::vector<std::string> expr = { "1", "2", "+", "3", "*"};
    std::cout << R"(Result of { "1", "2", "+", "3", "*" } is: )" << RPN(expr) << '\n';
    
    return 0;
}
```



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
  
  实现参考自[Rosetta Code](https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm#C.2B.2B)，写的实在是太漂亮了！仅仅做了少许改动，去掉了异常处理（编译器不支持），改了一些表述使其更符合规范。 限于篇幅，请见我的[Github](https://github.com/JianXinyu/ENGI-4892-Data-Structure-and-Algorithms/blob/master/Exercises/5Stack/mathExpression.cpp).

## Queue

就像stack，queue也是list。 但与stack不同的是，queue在一端插入，却在另一端删除。

queue的基本操作有:

- enqueue: inserts an element at the end of the list (called the rear)
- dequeue: deletes (and returns) the element at the start of the list (called the front)

