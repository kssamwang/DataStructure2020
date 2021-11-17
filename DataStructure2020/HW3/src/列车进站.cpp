#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>        //malloc/realloc函数
#include <cstring>
#include <stack>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
#define MAXN 1024
char in[MAXN] = { '\0' };
char out[MAXN] = { '\0' };
 
int main()
{
	scanf("%s", in);
	char ch = getchar();
	while (cin.getline(out,MAXN,'\n') && out[0])
	{
		int i = 0;
		int j = 0;
		bool check = true;
		stack<char> s;
		while (out[j])
		{
			if (s.empty())
			{
				s.push(in[i++]);
				continue;
			}
			while (s.top() != out[j])//等待下一个要出栈的先进栈
			{
				if(in[i])
					s.push(in[i++]);
				else//全都进栈了，但是栈顶还不是下一个要出队的
				{
					check = false;
					break;
				}
			}
			if (!check)
				break;
			if (!s.empty())//等到了下一个要出栈的进了栈，在栈顶
			{
				s.pop();
				j++;
			}
			else
			{
				check = false;
				break;
			}
		}
		if (check)
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	return 0;
}