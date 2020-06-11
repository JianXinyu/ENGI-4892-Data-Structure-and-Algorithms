#include <iostream>
#include <stack>
#include <string>
#include <list>
#include "math.h"

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
        return pow(a, b);
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
template <typename Iter>
float RPN(Iter begin, Iter end)
{
    std::stack<float> numPool;
    for(auto i = begin; i != end; i++)
    {
        char ch = (*i)[0];
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
    std::list<std::string> expr = { "1", "2", "+", "3", "*"};
    std::cout << R"(Result of { "1", "2", "+", "3", "*" } is: )" << RPN(expr.begin(), expr.end()) << '\n';
}

