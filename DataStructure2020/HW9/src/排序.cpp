#include <bits/stdc++.h>
using namespace std;
 
const int N = 100005;
int a[N];
int n;
 
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)scanf("%d", &a[i]);
	sort(a,a + n);
	for (int i = 0; i < n; i++)printf("%d ", a[i]);
	return 0;
}