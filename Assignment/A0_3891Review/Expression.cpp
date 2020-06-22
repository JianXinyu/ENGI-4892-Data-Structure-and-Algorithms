
#include "Expression.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace calc;

//! Class to store literal
// such a class is needed because:
// declaring an ExpPtr variable needs an instantiation of Expression class
class tmpLiteral: public Expression
{
    double literal;
public:
    //constructor
    tmpLiteral (double x):literal(x){ };

    //implement pure virtual function
    double evaluate() const{return literal;};
};


//! Turn type double to ExpPtr
ExpPtr Expression::Literal(double x){
    ExpPtr literal(new tmpLiteral(x) );
    return literal;
}

//! Return the substring representing first number in the string
// referrenced from https://www.engr.mun.ca/~anderson/teaching/3891/tutorial/9/
std::string GetNumber(const std::string& s)
{
    if (s.empty())
    {
        throw string("Your input string is empty!!");
    }

    // Find the first character that is not part of a number:
    // Here we consider space as part of number
    for (size_t i = 0; i < s.length(); i++)
    {
        const bool number = (s[i] >= '0' and s[i] <= '9');
        const bool decimal = (s[i] == '.');
        const bool space = (s[i] == ' ');
        if (not number and not decimal and not space)
        {
            // return a number
            return s.substr(0, i);
        }
    }

    // No non-number characters found: the whole thing must be a number.
    return s;
}


//! Parse a string containing literals, can only deal with either addition or multiplication
// referrence from https://www.engr.mun.ca/~anderson/teaching/3891/tutorial/9/
ExpPtr Expression::Parse(string s){
    // find the the substring representing first number in the string as the left-hand side
    const string lhsStr = GetNumber(s);
    // To convert it to type ExpPtr, convert it to type float first
    ExpPtr lhs = Literal(stof(lhsStr));

    // Find the position of the first operator in the string
    size_t opPosition = lhsStr.length();
    // If there is no operator
    if (opPosition == s.length())
    {
        // set right-hand side as zero. return the left-hand side
        ExpPtr rhs = Literal(0.0);
        return BinaryExpression::Add(move(lhs), move(rhs));
    }

    // get the first operator
    char op = s[opPosition];

    // get the rest of string not parsed yet
    const string restStr = s.substr(opPosition + 1);
    // find the next number
    string nextStr = GetNumber(restStr);

    // if the rest of the string is just a number
    if (nextStr.length() == restStr.length())
    {
        // get right-hand side
        ExpPtr rhs = Literal(stof(nextStr));
        // conduct calculation
        // parsing can only deal with either addition or multiplication
        if (op == '+'){
            return BinaryExpression::Add(move(lhs), move(rhs));
        }
        else if (op == '*'){
            return BinaryExpression::Multiply(move(lhs), move(rhs));
        }
        else{
            exit(1);
        }
    }

    // Otherwise, the rest of the string needs to be parsed again
    // set the result of the rest as right-hand side
    // hence, the order of operations are from right to left,
    // e.g. '2*3+4' will be calculated as 2*(3+4)=14
    ExpPtr rhs = Parse(restStr);
    // conduct calculation
    if (op == '+'){
        return BinaryExpression::Add(move(lhs), move(rhs));
    }
    else if (op == '*'){
        return BinaryExpression::Multiply(move(lhs), move(rhs));
    }
    else{
        exit(1);
    }
}


// Constructor: initialize parameters
BinaryExpression::BinaryExpression(ExpPtr lhs, ExpPtr rhs)
        : lhs_(move(lhs)), rhs_(move(rhs))
{
}

// Class to calculate and store the result
// such a class is needed because:
// to return an ExpPtr variable in BinaryExpression::Add
// needs an instantiation of Expression class
class tmpAdd : public BinaryExpression{
public:
    // constructor
    tmpAdd(ExpPtr lhs, ExpPtr rhs)
            : BinaryExpression(move(lhs), move(rhs))
            {}
    // implement pure virtual function
    double evaluate() const{
        return (lhs_->evaluate() + rhs_->evaluate());
    }
};

// turn two ExpPtr type variables into their sum of ExpPtr type
ExpPtr BinaryExpression::Add(ExpPtr lhs, ExpPtr rhs){
    ExpPtr addition (new tmpAdd(move(lhs), move(rhs)));
    return addition;
}


class tmpMul : public BinaryExpression{
public:
    // constructor
    tmpMul(ExpPtr lhs, ExpPtr rhs)
            : BinaryExpression(move(lhs), move(rhs))
            {}
    // implement pure virtual function
    double evaluate() const {
        return (lhs_->evaluate() * rhs_->evaluate());
    }
};

// turn two ExpPtr type variables into their product of ExpPtr type
ExpPtr BinaryExpression::Multiply(ExpPtr lhs, ExpPtr rhs){
    ExpPtr product (new tmpMul(move(lhs), move(rhs)));
    return product;
}

/*****************************Didn't use at this stage**********************************/

class tmpSub : public BinaryExpression{
public:
    // constructor
    tmpSub(ExpPtr lhs, ExpPtr rhs)
            : BinaryExpression(move(lhs), move(rhs))
    {}
    // implement pure virtual function
    double evaluate() const{
        return (lhs_->evaluate() - rhs_->evaluate());
    }
};

// turn two ExpPtr type variables into their difference of ExpPtr type
ExpPtr BinaryExpression::Subtract(ExpPtr lhs, ExpPtr rhs){
    ExpPtr difference (new tmpSub(move(lhs), move(rhs)));
    return difference;
}


class tmpDiv : public BinaryExpression{
public:
    // constructor
    tmpDiv(ExpPtr lhs, ExpPtr rhs)
            : BinaryExpression(move(lhs), move(rhs))
            {}
    // evaluate method.
    double evaluate() const{
        return  (lhs_->evaluate() / rhs_->evaluate());
    }
};

// turn two ExpPtr type variables into their quotient of ExpPtr type
ExpPtr BinaryExpression::Divide(ExpPtr lhs, ExpPtr rhs){
    ExpPtr quotient (new tmpDiv(move(lhs), move(rhs)));
    return quotient;
}
