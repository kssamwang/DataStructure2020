#include <iostream>
#include <cstdlib>        //malloc/reallocº¯Êý
#include <cstring>
#include <stack>
#include <ctype.h>
using namespace std;
 
bool div_0 = false;
 
enum class optr {
	PLUS = '+',
	MINUS = '-',
	MUL = '*',
	DIV = '/',
	LEFT_BRCKET = '(',
	RIGHT_BRCKET = ')',
	END = '#'
};
 
optr convert(const char ch)
{
	if (ch == '+')return optr::PLUS;
	if (ch == '-')return optr::MINUS;
	if (ch == '*')return optr::MUL;
	if (ch == '/')return optr::DIV;
	if (ch == '(')return optr::LEFT_BRCKET;
	if (ch == ')')return optr::RIGHT_BRCKET;
	if (ch == '#')return optr::END;
}
 
char precede(const optr l, const optr r)
{
	char ans = '>';
	switch (l)
	{
		case  optr::PLUS:
		{
			switch (r)
			{
				case  optr::PLUS:ans = '>'; break;
				case  optr::MINUS:ans = '>'; break;
				case  optr::MUL:ans = '<'; break;
				case  optr::DIV:ans = '<'; break;
				case  optr::LEFT_BRCKET:ans = '<'; break;
				case  optr::RIGHT_BRCKET:ans = '>'; break;
				case  optr::END:ans = '>'; break;
			}
			break;
		}
		case  optr::MINUS:
		{
			switch (r)
			{
				case  optr::PLUS:ans = '>'; break;
				case  optr::MINUS:ans = '>'; break;
				case  optr::MUL:ans = '<'; break;
				case  optr::DIV:ans = '<'; break;
				case  optr::LEFT_BRCKET:ans = '<'; break;
				case  optr::RIGHT_BRCKET:ans = '>'; break;
				case  optr::END:ans = '>'; break;
			}
			break;
		}
		case  optr::MUL:
		{
			switch (r)
			{
				case  optr::PLUS:ans = '>'; break;
				case  optr::MINUS:ans = '>'; break;
				case  optr::MUL:ans = '>'; break;
				case  optr::DIV:ans = '>'; break;
				case  optr::LEFT_BRCKET:ans = '<'; break;
				case  optr::RIGHT_BRCKET:ans = '>'; break;
				case  optr::END:ans = '>'; break;
			}
			break;
		}
		case  optr::DIV:
		{
			switch (r)
			{
				case  optr::PLUS:ans = '>'; break;
				case  optr::MINUS:ans = '>'; break;
				case  optr::MUL:ans = '>'; break;
				case  optr::DIV:ans = '>'; break;
				case  optr::LEFT_BRCKET:ans = '<'; break;
				case  optr::RIGHT_BRCKET:ans = '>'; break;
				case  optr::END:ans = '>'; break;
			}
			break;
		}
		case  optr::LEFT_BRCKET:
		{
			switch (r)
			{
				case  optr::PLUS:ans = '<'; break;
				case  optr::MINUS:ans = '<'; break;
				case  optr::MUL:ans = '<'; break;
				case  optr::DIV:ans = '<'; break;
				case  optr::LEFT_BRCKET:ans = '<'; break;
				case  optr::RIGHT_BRCKET:ans = '='; break;
				case  optr::END:ans = '<'; break;
			}
			break;
		}
		case  optr::RIGHT_BRCKET:
		{
			switch (r)
			{
				case  optr::PLUS:ans = '>'; break;
				case  optr::MINUS:ans = '>'; break;
				case  optr::MUL:ans = '>'; break;
				case  optr::DIV:ans = '>'; break;
				case  optr::LEFT_BRCKET:ans = '>'; break;
				case  optr::RIGHT_BRCKET:ans = '>'; break;
				case  optr::END:ans = '>'; break;
			}
			break;
		}
		case  optr::END:
		{
			switch (r)
			{
				case  optr::PLUS:ans = '<'; break;
				case  optr::MINUS:ans = '<'; break;
				case  optr::MUL:ans = '<'; break;
				case  optr::DIV:ans = '<'; break;
				case  optr::LEFT_BRCKET:ans = '<'; break;
				case  optr::RIGHT_BRCKET:ans = '<'; break;
				case  optr::END:ans = '='; break;
			}
			break;
		}
	}
	return ans;
}
 
int operation(const int l,const optr theta,const int r)
{
	int ans = 0;
	switch (theta)
	{
		case  optr::PLUS:ans = l + r; break;
		case  optr::MINUS:ans = l - r; break;
		case  optr::MUL:ans = l * r; break;
		case  optr::DIV:
		{
			if (r == 0)
			{
				div_0 = true;
				return ans;
			}
			ans = l / r; 
			break;
		}
	}
	return ans;
}
 
bool getnext(char* c)
{
	*c = cin.get();
	if (!((*c >= '0' && *c <= '9') || (*c == '+') || (*c == '-') || (*c == '*') || (*c == '/') || (*c == '(') || (*c == ')') || (*c == '=')))
		return false;
	if (*c == '=')
		*c = '#';
	return true;
}
 
int main()
{
	stack<char> OPTR;
	stack<int> OPND;
	OPTR.push('#');
	char c = cin.get();
	int optr_num = 0;
	while (c != '#' || OPTR.top() != '#')
	{
		if (isdigit(c))
		{
			optr_num = optr_num * 10 + (c - '0');
			if(!isdigit(cin.peek()))
			{
				OPND.push(optr_num);
				optr_num = 0;
				if (c != '#' && !getnext(&c))
				{
					cout << "ERROR";
					return 0;
				}
				continue;
			}
			if (c != '#' && !getnext(&c))
			{
				cout << "ERROR";
				return 0;
			}
		}
		else
		{
			switch (precede(convert(OPTR.top()), convert(c)))
			{
				case '<':
				{
					OPTR.push(c);
					if (c != '#' && !getnext(&c))
					{
						cout << "ERROR";
						return 0;
					}
					break; 
				}
				case '=':
				{
					OPTR.pop();
					if (c != '#' && !getnext(&c))
					{
						cout << "ERROR";
						return 0;
					}
					break;
				}
				case '>':
				{
					optr theta = convert(OPTR.top());
					OPTR.pop();
					int b = OPND.top();
					OPND.pop();
					int a = OPND.top();
					OPND.pop();
					int res = operation(a, theta, b);
					if (div_0)
					{
						cout << "ERROR";
						return 0;
					}
					OPND.push(res);
					break;
				}
			}
		}
	}
	cout << OPND.top();
	return 0;
}