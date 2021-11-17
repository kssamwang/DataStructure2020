#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
char s[1000000];
 
int main()
{
	int cnt = 0;
	while (1)
	{
		int high = 0;
		int newhigh = 0;
		int cur_high = 0;
		int cur_newhigh = 0;
		stack<int> path;
		scanf("%s", s);
		if (s[0] == '#')break;
		for (int i = 0; s[i]; i++)
		{
			if (s[i] == 'd')
			{
				cur_high++;
				cur_newhigh++;
				path.push(cur_newhigh);
			}
			else
			{
				cur_high--;
				cur_newhigh = path.top();
				path.pop();
			}
			high = max(high, cur_high);
			newhigh = max(newhigh, cur_newhigh);
		}
		printf("Tree %d: %d => %d\n", ++cnt, high, newhigh);
	}
	return 0;
}