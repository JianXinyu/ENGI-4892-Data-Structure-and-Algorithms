#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <list>
#include <cmath>

#include <regex>
#include <unordered_map>
#include <sstream>

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

// The following code is to implement shunting-yard algorithm
// Referred from https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm#C.2B.2B

using std::vector;
using std::string;

//-------------------------------------------------------------------------------------------------
// Stack
//-------------------------------------------------------------------------------------------------
// Let us co-opt a vector for our stack type.
// C++ pedants: no splicing possible == totally okay to do this.
//
// Note: C++ provides a more appropriate std::stack class, except that the task requires us to
// be able to display its contents, and that kind of access is an expressly non-stack behavior.
template <typename T>
struct stack : public std::vector <T>
{
    using base_type = std::vector <T> ;
    T        push ( const T& x ) { base_type::push_back( x ); return x; }
    const T& top  ()             { return base_type::back(); }
    T        pop  ()             { T x = std::move( top() ); base_type::pop_back(); return x; }
    bool     empty()             { return base_type::empty(); }
};

using Operator_Name = std::string;
using Precedence    = int;
enum class Associates { none, left_to_right, right_to_left };

// store the priority and associativity(left or right) information
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

//-------------------------------------------------------------------------------------------------
using Token = string;
//-------------------------------------------------------------------------------------------------
//the way to check a number is so elegant! Although I don't know how to use regular expression.
bool is_number           ( const Token& t ) { return regex_match( t, std::regex{ R"z((\d+(\.\d*)?|\.\d+)([Ee][\+\-]?\d+)?)z" } ); }
bool is_operator         ( const Token& t ) { return Operators.count( t ); }
bool is_open_parenthesis ( const Token& t ) { return t == "("; }
bool is_close_parenthesis( const Token& t ) { return t == ")"; }
bool is_parenthesis      ( const Token& t ) { return is_open_parenthesis( t ) or is_close_parenthesis( t ); }

//! Reload operator << to print std::vector type
template <typename T>
std::ostream& operator << ( std::ostream& outs, const std::vector <T> & xs )
{
    std::size_t n = 0;
    for (const auto& x : xs)
        outs << (n++ ? " " : "") << x;
    return outs;
}

//! display the procedures,
//! show the changes in the operator stack and RPN output as each individual token is processed
// didn't read through
#include <iomanip>
struct Progressive_Display
{
    string token_name;
    string token_type;

    Progressive_Display()  // Header for the table we are going to generate
    {
        std::cout << "\n"
                     "  INPUT ©¦ TYPE ©¦ ACTION           ©¦ STACK        ©¦ OUTPUT\n"
                     "©¤©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n";
    }

    Progressive_Display& operator () ( const Token& token )  // Ready the first two columns
    {
        token_name = token;
        token_type = is_operator   ( token ) ? "op"
                                             : is_parenthesis( token ) ? "()"
                                                                       : is_number     ( token ) ? "num"
                                                                                                 : "";
        return *this;
    }

    Progressive_Display& operator () (  // Display all columns of a row
            const string         & description,
            const stack  <Token> & stack,
            const vector <Token> & output )
    {
        std::ostringstream oss;
        oss << stack;
        std::cout                                                               << std::right
           << std::setw(  7 ) << token_name                            << " ©¦ " << std::left
           << std::setw(  4 ) << token_type                            << " ©¦ "
           << std::setw( 16 ) << description                           << " ©¦ "
           << std::setw( 12 ) << oss.str()                             << " ©¦ "
           <<                    output                                << "\n";
        return operator () ( "" );  // Reset the first two columns to empty for next iteration
    }
};

/**
 * Use Dijkstra¡¯s stack-based shunting-yard algorithm to convert an infix mathematical expression
 * into a postfix expression using reverse Polish notation (RPN)
 * @param  tokens: infix expression
 * @return output: postfix expression
 */
//-------------------------------------------------------------------------------------------------
vector <Token> infix2RPN( const vector <Token> & tokens )
//-------------------------------------------------------------------------------------------------
{
    vector <Token> output;
    stack  <Token> stack;

    Progressive_Display display;

    for (const auto& token : tokens)  // Shunting Yard takes a single linear pass through the tokens

        //.........................................................................
        if (is_number( token ))
        {
            output.push_back( token );
            display( token )( "num --> output", stack, output );
        }

            //.........................................................................
        else if (is_operator( token ) or is_parenthesis( token ))
        {
            display( token );

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
                    output.push_back( stack.pop() );
                    display( "pop --> output", stack, output );
                }

                // If we popped until '(' because token is ')', toss both parens
                if (is_close_parenthesis( token ))
                {
                    stack.pop();
                    display( "pop", stack, output );
                }
            }

            // Everything except ')' --> stack
            if (!is_close_parenthesis( token ))
            {
                stack.push( token );
                display( "push op", stack, output );
            }
        }

    // Anything left on the operator stack just gets moved to the output
    display( "END" );
    while (!stack.empty())
    {
        output.push_back( stack.pop() );
        display( "pop --> output", stack, output );
    }

    return output;
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

        // when encounter operator or parenthesis, we know that there is a complete number
        // so store the previous number and the operator or parenthesis
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
            // Append the numbers, if token is empty or space, then there is a complete number
            // otherwise, the number hasn't been completed yet
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
    // store the last element
    tokens.push_back( str );
    return tokens;
}


int main()
{
    std::vector<std::string> expr = { "1", "2", "+", "3", "*"};
    std::cout << R"(Result of { "1", "2", "+", "3", "*" } is: )" << RPN(expr) << '\n';

//    std::string expr2 = "1 + 2 * ( 3 + 4 )";
//    std::string expr2 = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3 ";
    std::string expr2 = "1 + 2 * ( 3 / 4 )-(5*6)";
    std::vector<std::string> tokens = getExpressionTokens( expr2 );
    auto rpn_expr = infix2RPN( tokens );
    auto result = RPN(rpn_expr);
    std::cout
            << "\nInfix = " << tokens
            << "\nRPN   = " << rpn_expr
            << "\nResult= " << result
            << "\n";

    return 0;
}
