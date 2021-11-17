#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;
 
#ifdef _MSC_VER
#pragma warning(disable:6031)
#endif
 
int a[100005];
 
int main()
{
	int n, k;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
	{
		int x;
		scanf("%d", &x);
		int l = 0;
		int r = n - 1;
		while (l < r)
		{
			int mid = l + (r - l) / 2;
			if (a[mid] >= x)
				r = mid;
			else
				l = mid + 1;
		}
		printf("%d\n", a[l] == x ? l : -1);
	}
	return 0;
}