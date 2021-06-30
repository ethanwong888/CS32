#include "Map.h"
#include<iostream>
#include<cctype>
#include<cassert>
#include<string>
#include<stack>
using namespace std;

string noSpace(string infix);

bool validSyntax(string infix);

int precedence(char r);
string toPostfix(string infix);

bool checkValidity(string postfix, const Map& values);
int evaluate(string infix, const Map& values, string& postfix, int& result);



string noSpace(string infix)
{
	string newString;
	for (int w = 0; w < infix.size(); w++)
	{
		if (infix[w] != ' ')
		{
			newString += infix[w];
		}
	}
	return newString;
}




bool validSyntax(string infix)
{
	stack<char> parentheses;
	string expression = noSpace(infix);
	if (expression.length() == 0)
	{
		return false;
	}


	if (!islower(expression[0]) && expression[0] != '(')
	{
		return false;
	}

	if (expression[0] == '(')
	{
		parentheses.push(expression[0]);
	}

	char c = expression[0];
	for (int p = 1; p < expression.size(); p++)
	{
		c = expression[p];
		switch (c)
		{
		case '(':
				if (expression[p - 1] == ')' || isalpha(expression[p - 1]))
				{
					return false;
				}
			parentheses.push(p); break;
		case ')':
			if (expression[p - 1] == '(' || expression[p - 1] == '+' || expression[p - 1] == '-' || expression[p - 1] == '/' || expression[p - 1] == '*')
			{
				return false;
			}
			if (parentheses.empty())
			{
				return false;
			}
			parentheses.pop(); break;
		case '+': 
		case '-':
		case '/':
		case '*':
			if (expression[p - 1] == '(' || expression[p - 1] == '+' || expression[p - 1] == '-' || expression[p - 1] == '/' || expression[p - 1] == '*')
			{
				return false;
			}

			if (expression[p - 1] != ')' && !isalpha(expression[p - 1]))
			{
				return false;
			}
			break;
		default: 
			if(expression[p - 1] == ')' || isalpha(expression[p-1]))
			{ 
				return false;
			}
			if (isupper(c) || !isalpha(c))
			{
				return false;
			}
			break;
		}
	}
	if (!parentheses.empty())
	{
		return false;
	}

	if (c != ')' && !isalpha(c))
	{
		return false;
	}
	return true;
}



int precedence(char r)
{
	switch (r)
	{
	case '+':
	case'-':
		return 1; 
	case '/':
	case '*':
		return 4;
	default:
		return 56;
	}
}


string toPostfix(string infix) 
{
	string postfix = "";
	stack<char> operators;
	for (int p = 0; p < infix.size(); p++)
	{
		char h = infix[p];

		if (isalpha(h))
		{
			postfix += h;
			continue;
		}

		switch (h)
		{
		case '(':
			operators.push(h);
			break;
		case ')':
			while (operators.top() != '(')
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.pop();
			break;
		case '+':
		case '*':
		case '/':
		case '-':
			while (!operators.empty() && (precedence(h) <= precedence(operators.top())) && operators.top() != '(')
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.push(h);
			break;
		}
	}
	while (!operators.empty())
	{
		postfix += operators.top();
		operators.pop();
	}
	return postfix;
}



bool checkValidity(string postfix, const Map& values)
{
	for (int i = 0; i < postfix.size(); i++)
	{
		if (islower(postfix[i]))
		{
			if (!values.contains(postfix[i]))  
			{
				return false;
			}
		}
	}
	return true;
}




int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	if (validSyntax(infix) == false)
	{
		return 1;
	}

	postfix = toPostfix(infix);

	if (checkValidity(postfix, values) == false)
	{
		return 2;
	}

	stack<int> equation;

	for (int y = 0; y < postfix.size(); y++)
	{
		char j = postfix[y];

		if (isalpha(j))
		{
			int number;
			values.get(j, number);  
			equation.push(number);
		}

		else
		{
			int beta = equation.top();
			equation.pop();

			int alpha = equation.top();
			equation.pop();

			switch (j)
			{
			case '-' : 
				equation.push(alpha - beta);
				break;
			case '+' : 
				equation.push(alpha + beta);
				break;
			case '*' :
				equation.push(alpha * beta); 
				break;
			case '/' :
				if (beta == 0)
				{
					return 3;
				}
				equation.push(alpha / beta);
				break;
			}
		}
	}
	result = equation.top();
	return 0;
}

/*
int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&  pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:


	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 && pf == "ab*" && answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 && pf == "yoau-*+" && answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 && pf == "oyy-/" && answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 && pf == "a" && answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 && pf == "a" && answer == 3);
	cout << "Passed all tests" << endl;
}
*/