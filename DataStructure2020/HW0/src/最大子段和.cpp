#include <iostream>
#include <cstdio>
using namespace std;
 
int main()
{
	int n = 0;
	scanf("%d",&n);
	int t = 0;
	int sum = 0;
	int ans = 0x80000000;
	while(n--)
	{
		scanf("%d",&t);
		sum = (sum < 0 ? t : sum + t);
		ans = (ans > sum ? ans : sum);
	}
	printf("%d",ans);
	return 0;
}