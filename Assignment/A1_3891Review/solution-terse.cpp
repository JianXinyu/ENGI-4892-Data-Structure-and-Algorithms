/*!
 * @file      Expression.cpp
 * @brief     Definition of the calc::Expression class (and subclasses).
 *
 * @author    Jonathan Anderson <jonathan.anderson@mun.ca>
 * @copyright (c) 2016 Jonathan Anderson. All rights reserved.
 * @license   Apache License, Version 2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include "Expression.h"

#include <functional>
#include <iostream>
#include <string>

using namespace calc;
using namespace std;


class Value : public Expression
{
public:
	Value(double v) : value_(v) {}

	double evaluate() const override { return value_; }

	static ExpPtr Parse(string);

private:
	const double value_;
};


using BinaryOperator = function<double (double, double)>;

class BinaryExprImpl : public BinaryExpression
{
public:
	static ExpPtr Create(ExpPtr lhs, ExpPtr rhs, BinaryOperator op)
	{
		return ExpPtr(new BinaryExprImpl(move(lhs), move(rhs), op));
	}

	BinaryExprImpl(ExpPtr lhs, ExpPtr rhs, BinaryOperator op)
		: BinaryExpression(move(lhs), move(rhs)), op_(op)
	{
	}

	double evaluate() const override
	{
		return op_(lhs_->evaluate(), rhs_->evaluate());
	}

private:
	BinaryOperator	op_;
};


//! Is this character a number?
static bool IsNumber(char c)
{
	return (c >= '0' and c <= '9');
}


/**
 * Get the next number from a string.
 *
 * @pre    the string should start with a number
 */
static string GetNumber(const string& s)
{
	if (s.empty() or not IsNumber(s[0]))
	{
		throw string("'" + s + "' does not start with a number");
	}

	// Find the first character that is not part of a number:
	for (size_t i = 0; i < s.length(); i++)
	{
		const bool number = IsNumber(s[i]);
		const bool decimal = (s[i] == '.');

		if (not number and not decimal)
		{
			return s.substr(0, i);
		}
	}

	// No non-number characters found: the whole thing must be a number.
	return s;
}


ExpPtr Value::Parse(string s)
{
	return ExpPtr(new Value(stof(s)));
}


ExpPtr Expression::Parse(string s)
{
	// First, consume leading whitespace:
	size_t pos = 0;
	while (pos < s.length() and s[pos] == ' ')
	{
		pos++;
	}

	s = s.substr(pos);

	// Find the left-hand side and use the std::stof() function
	// to convert it into a number:
	string lhsStr = GetNumber(s);
	ExpPtr lhs = Value::Parse(lhsStr);

	// Find the operator:
	pos = lhsStr.length();

	while (pos < s.length() and s[pos] == ' ')
	{
		pos++;
	}

	if (pos == s.length())
	{
		return lhs;
	}

	char op = s[pos];

	// Skip any more spaces:
	size_t nextStart = pos + 1;
	while (nextStart < s.length() and s[nextStart] == ' ')
	{
		nextStart++;
	}

	const string theRest = s.substr(nextStart);
	ExpPtr rhs = Parse(theRest);
	BinaryOperator f;

	switch (op)
	{
	case '+':
		return BinaryExpression::Add(move(lhs), move(rhs));

	case '-':
		return BinaryExpression::Subtract(move(lhs), move(rhs));

	case '*':
		return BinaryExpression::Multiply(move(lhs), move(rhs));

	case '/':
		return BinaryExpression::Divide(move(lhs), move(rhs));

	default:
		throw string("unsupported operator: " + string(1, op));
	}
}


ExpPtr Expression::Literal(double x)
{
	return ExpPtr(new Value(x));
}


BinaryExpression::BinaryExpression(ExpPtr lhs, ExpPtr rhs)
	: lhs_(move(lhs)), rhs_(move(rhs))
{
}


ExpPtr BinaryExpression::Add(ExpPtr lhs, ExpPtr rhs)
{
	return BinaryExprImpl::Create(move(lhs), move(rhs),
		[](double x, double y) { return x + y; });
}

ExpPtr BinaryExpression::Subtract(ExpPtr lhs, ExpPtr rhs)
{
	return BinaryExprImpl::Create(move(lhs), move(rhs),
		[](double x, double y) { return x - y; });
}


ExpPtr BinaryExpression::Multiply(ExpPtr lhs, ExpPtr rhs)
{
	return BinaryExprImpl::Create(move(lhs), move(rhs),
		[](double x, double y) { return x * y; });
}


ExpPtr BinaryExpression::Divide(ExpPtr lhs, ExpPtr rhs)
{
	return BinaryExprImpl::Create(move(lhs), move(rhs),
		[](double x, double y) { return x / y; });
}