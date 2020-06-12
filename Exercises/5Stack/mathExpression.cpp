#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <regex>
#include <unordered_map>

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

//Referred from https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm#C.2B.2B
using Operator_Name = std::string;
using Precedence    = int;
enum class Associates { none, left_to_right, right_to_left };

struct Operator_Info { Precedence precedence; Associates associativity; };

std::unordered_map <Operator_Name, Operator_Info>  Operators =
        {
                { "^", { 4, Associates::right_to_left } },
                { "*", { 3, Associates::left_to_right } },
                { "/", { 3, Associates::left_to_right } },
                { "+", { 2, Associates::left_to_right } },
                { "-", { 2, Associates::left_to_right } },
        };

Precedence precedence   ( const Operator_Name& op ) { return Operators[ op ].precedence; }
Associates associativity( const Operator_Name& op ) { return Operators[ op ].associativity; }

bool is_number           ( const std::string& t ) { return regex_match( t, std::regex{ R"z((\d+(\.\d*)?|\.\d+)([Ee][\+\-]?\d+)?)z" } ); }
bool is_operator         ( const std::string& t ) { return Operators.count( t ); }
bool is_open_parenthesis ( const std::string& t ) { return t == "("; }
bool is_close_parenthesis( const std::string& t ) { return t == ")"; }
bool is_parenthesis      ( const std::string& t ) { return is_open_parenthesis( t ) or is_close_parenthesis( t ); }

/**
 * Use Dijkstra’s stack-based shunting-yard algorithm to convert an infix mathematical expression
 * into a postfix expression using reverse Polish notation (RPN)
 * @param  tokens: infix expression
 * @return output: postfix expression
 */
std::vector<std::string> infix2RPN(const std::vector<std::string> &tokens)
{
    std::vector<std::string> output;
    std::stack<std::string> stack;

    for(const auto& token: tokens)
    {
        if(is_number( token ))
        {
            output.push_back( token );
        }
        else if(is_operator( token ))
        {
            while( !stack.empty() && is_operator(stack.top()))
            {
                if((associativity( token ) == Associates::left_to_right && precedence( token ) <= precedence( stack.top() ))
                    || (associativity( token ) == Associates::right_to_left && precedence(( token )) < precedence( stack.top() )) )
                {
                    output.push_back( stack.top() );
                    stack.pop();
                    break;
                }
            }
            stack.push( token );
        }
        else if(is_open_parenthesis( token ))
        {
            stack.push( token );
        }
        else if(is_close_parenthesis( token ))
        {
            while( !stack.empty() && !is_open_parenthesis( stack.top() ))
            {
                output.push_back( stack.top() );
                stack.pop();
            }
            if ( !stack.empty() ) stack.pop();
        }
    }

    while( !stack.empty() )
    {
        output.push_back( stack.top() );
        stack.pop();
    }

    return output;
}

using namespace std;
using Token = string;


vector <Token> parse( const vector <Token> & tokens )
//-------------------------------------------------------------------------------------------------
{
    vector <Token> output;
    stack  <Token> stack;


    for (auto token : tokens)  // Shunting Yard takes a single linear pass through the tokens

        //.........................................................................
        if (is_number( token ))
        {
            output.push_back( token );
        }

            //.........................................................................
        else if (is_operator( token ) or is_parenthesis( token ))
        {

            if (!is_open_parenthesis( token ))
            {
                // pop --> output
                //   : until '(' if token is ')'
                //   : while prec(token) > prec(top)
                //   : while prec(token) == prec(top) AND assoc(token) is left-to-right
                while (!stack.empty()
                       and (   (is_close_parenthesis( token ) and !is_open_parenthesis( stack.top() ))
                               or (precedence( stack.top() ) > precedence( token ))
                               or (    (precedence( stack.top() ) == precedence( token ))
                                       and (associativity( token ) == Associates::left_to_right))))
                {
                    output.push_back( stack.top() );
                    stack.pop();
                }

                // If we popped until '(' because token is ')', toss both parens
                if (is_close_parenthesis( token ))
                {
                    stack.pop();
                }
            }

            // Everything except ')' --> stack
            if (!is_close_parenthesis( token ))
            {
                stack.push( token );
            }
        }

            //.........................................................................
//        else throw error( "unexpected token: ", token );

    // Anything left on the operator stack just gets moved to the output

    while (!stack.empty())
    {
        output.push_back( stack.top() );
        stack.pop();
    }

    return output;
}

//! Reload operator << to print std::vector type
template <typename T> std::ostream& operator << ( std::ostream& outs, const std::vector <T> & xs )
{
    std::size_t n = 0;  for (auto x : xs) outs << (n++ ? " " : "") << x;  return outs;
}

//Referred from https://www.technical-recipes.com/2011/a-mathematical-expression-parser-in-java-and-cpp/#DownloadUpdate
/**
 * convert a string type expression into std::vector<std::string> type
 * @param expression: string type
 * @return tokens: std::vector<std::string> type
 */
std::vector<std::string> getExpressionTokens( const std::string& expression )
{
    std::vector<std::string> tokens;
    std::string str;

    for (char i : expression)
    {
        const std::string token( 1, i );

        if ( is_operator( token ) || is_parenthesis( token ) )
        {
            if ( !str.empty() )
            {
                tokens.push_back( str ) ;
            }
            str = "";
            tokens.push_back( token );
        }
        else
        {
            // Append the numbers
            if ( !token.empty() && token != " " )
            {
                str.append( token );
            }
            else
            {
                if ( !str.empty() )
                {
                    tokens.push_back( str );
                    str = "";
                }
            }
        }
    }

    return tokens;
}


int main()
{
    std::vector<std::string> expr = { "1", "2", "+", "3", "*"};
    std::cout << R"(Result of { "1", "2", "+", "3", "*" } is: )" << RPN(expr) << '\n';

//    std::string expr2 = "( 1 + 2) * ( 3 / 4 )-(5+6)";
    std::string expr2 = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    std::vector<std::string> tokens = getExpressionTokens( expr2 );
    std::cout << parse(tokens) ;

}

